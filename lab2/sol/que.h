#include <stdlib.h> 
typedef struct element element ; 
typedef struct queue queue ;
typedef element* Element ; 
typedef queue* Queue ; 
struct element {
    int key ; 
    struct element* next ; 
};
struct queue {
    int size ; 
    struct element *head , *tail ; 
};
Queue newQ();
int isEmptyQ(Queue q);
Queue delQ(Queue q);
Element front(Queue q);
Queue addQ(Queue q, Element e);
int lengthQ(Queue q);

