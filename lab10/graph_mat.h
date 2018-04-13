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

typedef struct graph_mat graph_mat ;

struct graph_mat {
    int vertices , edges ;
    int isDirected ; 
    int **mat ;
};

// create the graph with adjacency matrix 
graph_mat* createMatGraph(int numV , int isDirected) ;


graph_mat* addEdge(graph_mat* g , vertex* u , vertex* v);

int degree(graph_mat* g , vertex* v);

// list of adjacent nodes
list* getAdjacent(graph_mat* g , vertex* v) ;

void BFS(graph_mat* g , vertex* start) ;
