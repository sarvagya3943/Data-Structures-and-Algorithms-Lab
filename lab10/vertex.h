#ifndef LIST 
#define LIST
    #include "list.h"
#endif
#include <stdlib.h> 
#include <stdio.h> 
#define MAX 100005 // max number of vertices , the way to avoid this will require some more code and i dont want to 


typedef struct vertex vertex ;

struct vertex {
    int label , visited , depth ; 
    list* neighbours ;
};

extern vertex* mapIndexToVertex[MAX] ;
vertex* newVertex();

