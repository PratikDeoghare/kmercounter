

#ifndef stream_summary_h_
#define stream_summary_h_

#include <iostream> 
#include <vector> 
#include <set> 
#include "doubly_linked_list.h" 

template<typename NodeT> 
struct Bucket{ 
    size_t count = 0;
    doubly_linked_list<NodeT> nodes; 
    Bucket<NodeT> * next; 
    Bucket<NodeT> * prev; 
    Bucket(size_t c){
        next = this; 
        prev = this; 
        count = c;
    } 
    void print() const {
        std::cout << count << " ==> " << std::endl; 
        nodes.print(); 
    } 
}; 


template<typename NodeT, typename NodeT_cmp> 
class StreamSummary{ 
    typename std::set<NodeT*, NodeT_cmp> nodes; 
    doubly_linked_list<Bucket<NodeT> > buckets; 
    size_t m; 

    public: 
    StreamSummary(size_t counters) {
        m = counters; 
        buckets.init(new Bucket<NodeT>(1)); 
    } 

    void update(NodeT * node){
        typename std::set<NodeT*, NodeT_cmp>::iterator it = nodes.find(node); 
        if(it != nodes.end()){
            delete node; 
            incr(*it); 
        } else if ( nodes.size() < m) { 
            nodes.insert(node); 
            node->bucket = buckets.head;
            buckets.head->nodes.push_front(node);
        } else { 
            NodeT * t = buckets.head->nodes.head; 
            nodes.erase(t);
            t->kmer = node->kmer;
            t->eps = t->bucket->count; 
            nodes.insert(t);
            incr(t); 
            delete node; 
        } 
    } 

    void print_buckets() const {
        buckets.print(); 
    } 

    const std::set<NodeT*, NodeT_cmp>& monitored_nodes() const {
        return nodes; 
    } 

    private: 
    void incr(NodeT * node){

        if(! node->bucket){
            node->bucket = buckets.head; 
            buckets.head->nodes.push_front(node); 
        }  

        Bucket<NodeT> * buck = node->bucket; 

        if(node->bucket->count + 1 != node->bucket->next->count){
            // no bucket with +1 size 
            buckets.link_after(node->bucket, new Bucket<NodeT>(node->bucket->count + 1)); 
            node->bucket->nodes.unlink(node); 
            node->bucket = node->bucket->next; 
            node->bucket->nodes.init(node); 
        } else {
            // bucket with +1 size exists 
            node->bucket->nodes.unlink(node); 
            node->bucket = node->bucket->next; 
            node->bucket->nodes.push_front(node); 
        } 

        if( buck->nodes.empty()){
            buckets.unlink(buck);
            delete buck;
        } else {

        } 

    } 



};


#endif //stream_summary_h_

