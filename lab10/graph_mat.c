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
    #include "graph_mat.h" 
#endif
#include <stdio.h> 
#include <stdlib.h> 

// create the graph with adjacency matrix 
graph_mat* createMatGraph(int numV , int isDirected) {
    graph_mat* g = (graph_mat*) malloc(sizeof(graph_mat)) ;
    g->vertices = numV ; 
    g->mat = (int**) malloc(numV * sizeof(int*)) ; 
    g->isDirected = isDirected ; 
    int i ; 
    for(i = 0 ; i < numV ; ++i) {
        g->mat[i] = (int*) malloc(numV * sizeof(int)) ; 
    }
    return g ;
}

graph_mat* addEdge(graph_mat* g , vertex* u , vertex* v) {
    g->edges++ ; 
    int labelu = u->label , labelv = v->label ; 
    g->mat[labelu][labelv] = 1 ; 
    if(!g->isDirected) g->mat[labelv][labelu] = 1 ; 
    return g ;
}

int degree(graph_mat* g , vertex* v) {
    int deg = 0 ; 
    int i ; 
    for(i = 0 ; i < g->vertices ; ++i) {
        deg += g->mat[v->label][i] ; 
    }
    return deg ;
}

// list of adjacent nodes
list* getAdjacent(graph_mat* g , vertex* v) {
    list* res = newList() ; 
    int i ; 
    for(i = 0 ; i < g->vertices ; ++i) {
        if(g->mat[v->label][i] == 1) {
            res = insert(res , newNode(v->label)) ; 
        }
    }
    return res ; 
}

void BFS(graph_mat* g , vertex* start) {
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
