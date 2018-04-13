#ifndef VERTEX 
#define VERTEX
    #include "vertex.h" 
#endif
#include <stdio.h> 
#include <stdlib.h> 

static int count = 0 ; 

vertex* newVertex() {
    vertex* v = (vertex*) malloc(sizeof(vertex)) ;
    mapIndexToVertex[count] = v ; 
    v->label = count++ ; 
    v->visited = 0 ; 
    v->neighbours = newList() ; 
    return v; 
}
