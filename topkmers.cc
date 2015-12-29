

#include "stream_summary.h" 
#include <iostream> 
#include <fstream> 
#include <vector> 
#include <queue> 
using namespace std; 

// kmer node 
struct Node{
    Node * next; 
    Node * prev; 
    Bucket<Node> * bucket; 
    string kmer; 
    size_t eps = 0;

    void print() const { 
        std::cout << "\t" 
                  << kmer << " " 
                  << eps << " " 
                  << (bucket->count - eps) 
                  << std::endl; 
    }

    Node(string s){
        kmer = s;
        next = this; 
        prev = this; 
        bucket = NULL; 
    } 
}; 

struct Node_cmp {
    bool operator() ( const Node * a, const Node * b){
        return a->kmer < b->kmer; 
    } 
}; 

struct Node_Priority_cmp {
    bool operator() ( const Node * a, const Node * b){
        return (a->bucket->count - a->eps ) >= (b->bucket->count - b->eps);
    } 
}; 

void stream_kmers(const string& filename, StreamSummary<Node,Node_cmp>& ss, const size_t k){
    ifstream in(filename); 
    string line; 
    size_t c = 0; 
    while( getline(in, line)){ 
        if(c % 4 == 1 ){ 
            for(int i = 0; i < line.size() - k + 1; ++i){
                ss.update(new Node(line.substr(i, k)));
            } 
        } 
        c++;
    } 
} 

void print_top(const StreamSummary<Node, Node_cmp>& ss, size_t n){ 
    auto nodes = ss.monitored_nodes(); 
    priority_queue<Node*, vector<Node*>,  Node_Priority_cmp> pq; 
    Node_Priority_cmp cmp;

    for( auto y : nodes){ 
        if( pq.size() < n ) {
            pq.push(y); 
        } else { 
            if( cmp(y, pq.top()) ) { 
                pq.pop(); 
                pq.push(y);
            } 
        } 
    } 

    vector<Node*> v; 
    while( ! pq.empty()) { 
        v.push_back( pq.top() ); 
        pq.pop();
    } 

    for(auto it=v.rbegin(); it != v.rend(); ++it){
        std::cout << (*it)->kmer << " " << ( (*it)->bucket->count - (*it)->eps) << std::endl;
    } 
}


int main(int argc, char * argv[]){

    size_t k = atoi(argv[2]); 
    size_t t = atoi(argv[3]);
    size_t m = 7000;
    if( argc >= 5) { 
        m = atoi(argv[4]);
    }
    StreamSummary<Node, Node_cmp> ss(m);
    stream_kmers( argv[1], ss,  k);
    print_top(ss, t);
    return 0;
} 



