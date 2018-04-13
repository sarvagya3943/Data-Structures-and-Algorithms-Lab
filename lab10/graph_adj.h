
#ifndef LIST
#define LIST
    #include "list.h"
#endif 
#ifndef VERTEX
#define VERTEX
    #include "vertex.h"
#endif
#include <stdlib.h>
#include <stdio.h> 

typedef struct graph_adj graph_adj ;

struct graph_adj {
    int vertices , edges ;
    int isDirected ; 
    list **adj ;
};

// create the graph with adjacency matrix 
graph_adj* createAdjGraph(int numV , int isDirected) ;

graph_adj* addEdge(graph_adj* g , vertex* u , vertex* v);

int degree(graph_adj* g , vertex* v);

// list of adjacent nodes
list* getAdjacent(graph_adj* g , vertex* v) ;

void BFS(graph_adj* g , vertex* start) ;
