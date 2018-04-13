#include <stdio.h> 
#include <stdlib.h> 

typedef struct node node ;

struct node {
    int label ; 
    struct node* next ;
};

typedef struct list list ; 

struct list {
    int size ; 
    node *head , *tail ;
};

node* newNode(int key) ;
list* newList() ; 
list* insert(list* l , node* temp) ;
list* delete(list* l) ;
int isEmpty(list* l) ;
