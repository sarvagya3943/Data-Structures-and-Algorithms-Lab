
#ifndef LIST
#define LIST
    #include "list.h"
#endif 
#ifndef VERTEX
#define VERTEX
    #include "vertex.h"
#endif
#ifndef GRAPH_MAT 
#define GRAPH_MAT 
    #include "graph_adj.h" 
#endif
#include <stdio.h> 
#include <stdlib.h> 

// create the graph with adjacency list 
graph_adj* createAdjGraph(int numV , int isDirected) {
    graph_adj* g = (graph_adj*) malloc(sizeof(graph_adj)) ;
    g->vertices = numV ; 
    g->adj = (list**) malloc(numV * sizeof(list*)) ; 
    g->isDirected = isDirected ; 
    int i ; 
    for(i = 0 ; i < numV ; ++i) {
        g->adj[i] = newList() ; 
    }
    return g ;
}

graph_adj* addEdge(graph_adj* g , vertex* u , vertex* v) {
    g->edges++ ; 
    int labelu = u->label , labelv = v->label ; 
    g->adj[labelu] = insert(g->adj[labelu] , newNode(labelv)) ; 
    if(!g->isDirected) {
        g->adj[labelv] = insert(g->adj[labelv] , newNode(labelu)) ; 
    }
    return g ;
}

int degree(graph_adj* g , vertex* v) {
    int labelv = v->label ; 
    return g->adj[labelv]->size ; 
}

// list of adjacent nodes
list* getAdjacent(graph_adj* g , vertex* v) {
    return g->adj[v->label] ;   
}

void BFS(graph_adj* g , vertex* start) {
    list* queue = newList() ; // i feel should be implemented separately but i dont care 
    int numV = g->vertices ; 
    int i ; 
    for(i = 0 ; i < numV ; ++i) {
        vertex* v = mapIndexToVertex[i] ;
        v->visited = 0 ; 
    }
    start->visited = 1 ; 
    start->depth = 0 ; 
    queue = insert(queue , newNode(start->label)) ;
    while(!isEmpty(queue)) {
        node* front = queue->head ;
        queue = delete(queue) ; 
        vertex* frontVertex = mapIndexToVertex[front->label] ;
        list* adj = getAdjacent(g , frontVertex) ;
        while(adj->size > 0) {
            node *curr = adj->head ; 
            adj = delete(adj) ; 
            vertex* child = mapIndexToVertex[curr->label] ;
            if(!child->visited) {
                child->visited = 1 ; 
                child->depth = frontVertex->depth + 1 ; 
                queue = insert(queue , curr) ;
            }
        }
    }
}
