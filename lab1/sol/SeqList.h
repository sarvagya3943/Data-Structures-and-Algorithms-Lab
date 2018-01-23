#include <stdlib.h> 

typedef struct element element ; 
typedef element* Element ;
typedef struct seqList seqList ; 
typedef seqList* SeqList ; 

struct element {
    int key ; 
    struct element* next ; 
};

struct seqList {
    int size ; 
    Element front , back ; 
};

SeqList newList(); 
SeqList insertInOrder(SeqList sl , Element e) ;
SeqList insertAtFront(SeqList sl , Element e); 
SeqList insertAtEnd(SeqList sl , Element e) ;
SeqList delete(SeqList sl , Element e) ;
SeqList deleteAtFront(SeqList sl) ;
Element find(SeqList sl , int key) ;

