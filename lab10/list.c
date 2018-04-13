#ifndef LIST 
#define LIST
    #include "list.h" 
#endif
#include <stdlib.h>
#include <stdio.h>

list* newList() {
    list* res = (list*)malloc(sizeof(list)) ;
    res->size = 0 ; 
    res->head = res->tail = NULL ; return res ;
}

node* newNode(int key) {
    node* res = (node*)malloc(sizeof(node)) ;
    res->label = key ; 
    res->next = NULL ; 
    return res ; 
}

list* insert(list* l , node* temp) {
    if(l->size == 0) {
        l->size++ ; 
        l->head = l->tail = temp ; 
        return l ; 
    }
    temp->next = NULL ; 
    l->tail->next = temp ; 
    l->tail = temp ; 
    l->size++ ; 
    return l ; 
}

int isEmpty(list* l) {
    return (l->size > 0) ; 
}

list* delete(list* l) {
    if(l->size == 0) return l ; 
    node* temp = l->head ; 
    l->head = l->head->next ; 
    free(temp) ; 
    l->size-- ; 
    return l ;
}
