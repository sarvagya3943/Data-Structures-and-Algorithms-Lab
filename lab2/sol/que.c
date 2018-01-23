#include "que.h" 
#include <stdio.h>

Queue newQ() {
    Queue newQueue = (Queue)malloc(sizeof(queue));
    newQueue->size = 0 ; 
    newQueue->head = newQueue->tail = NULL ; 
    return newQueue ;
}
int isEmptyQ(Queue q) {
    if(q == NULL || q->size == 0) return 1;
    return 0 ;
}
Element front(Queue q) {
    if(q == NULL) return NULL ; 
    return q->head ; 
}
int lengthQ(Queue q) {
    if(q == NULL) return 0 ; 
    return q->size ; 
}
Queue delQ(Queue q) {
    if(q == NULL || q->size == 0) return q ;
    Element curr = q->head ; 
    q->size-- ;
    q->head = q->head->next ; 
    if(q->head == NULL) q->tail = NULL ; 
    free(curr) ; 
    return q ; 
}
Queue addQ(Queue q , Element e) {
    if(q == NULL) {
        q = newQ() ; 
    }
    if(q->size == 0) {
        q->size = 1 ; 
        q->head = q->tail = e ; 
        return q ; 
    }
    q->size++ ; 
    q->tail->next = e ; 
    e->next = NULL ; 
    q->tail = e ; 
    return q ; 
}

