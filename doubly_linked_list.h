

#ifndef doubly_linked_list_h_ 
#define doubly_linked_list_h_ 

#include <cstddef> 

template<typename T> 
struct doubly_linked_list{ 
    T * head; 
    doubly_linked_list(){
        head = NULL;
    } 

    void init(T* h) {
        head = h;
        head->next = h;
        head->prev = h;
    } 

    void push_front(T * node) {
        if(!head){
            init(node); 
            return; 
        } 
        link_before(head, node);
        head = node; 
    } 

    void link_after(T* t, T* node){
        t->next->prev = node; 
        node->next = t->next; 
        t->next = node; 
        node->prev = t; 
    } 

    void link_before(T* t, T* node){
        t->prev->next = node; 
        node->prev = t->prev; 
        t->prev = node;
        node->next = t; 
        if(t == head){
            head = node; 
        } 
    } 

    void unlink(T* node){
        if(node == head){
            if( node->next != node ) {
                head = node->next; 
            } else {
                head = NULL;
            } 
        } 
        node->next->prev = node->prev; 
        node->prev->next = node->next; 
    } 

    void print() const {
        if(head == NULL) return ;
        T * curr = head;  
        T * next; 
        do {
            next = curr->next; 
            curr->print();  
            curr = next;
        } while( curr != head); 
    } 

    bool empty() const {
        return (head == NULL);
    }

    ~doubly_linked_list(){
        if(head == NULL) return;
        T * curr = head;  
        T * next; 
        do {
            next = curr->next; 
            delete curr; 
            curr = next;
        } while( curr != head); 
    } 

};


#endif // doubly_linked_list_h_ 
