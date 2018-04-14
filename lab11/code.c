#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FNAME "graph0.txt"
#define MAX_VERTICES 100

typedef struct Edge Edge;
typedef struct EdgeList EdgeList;
typedef struct AdjList AdjList;
typedef struct list list ;

struct Edge{
	int u,v;
};

Edge makeEdge(int u,int v) {
	Edge x ;
	x.u=u;
	x.v=v;
	return x ;
}

struct EdgeList{
	int sz;
	Edge *arr;
};

EdgeList *createEdgeList(char *name) {
	int sz=0;
	FILE *fptr=fopen(name,"r");
	while(!feof(fptr)) {
		int x,y;
		fscanf(fptr,"%d %d\n",&x,&y);
		//printf("%d %d\n",x,y);
		sz++;
	}

	//printf("%d\n",sz);
	EdgeList *e = (EdgeList*)malloc(sizeof(EdgeList));
	e->sz=sz;
	e->arr=(Edge*)malloc(sizeof(Edge)*sz);
	
	fptr=fopen(name,"r");
	sz=0;
	while(!feof(fptr)) {
		int x,y;
		fscanf(fptr,"%d %d\n",&x,&y);
		(e->arr)[sz++]=makeEdge(x,y);
	}
	
	return e;
}

struct AdjList {
	int sz,cap;
	int *neighbours;
};

void addNeighbour(AdjList *adj,int u,int v) {
	AdjList *x = adj+u;
	if(x->sz==x->cap) {
		if(x->cap==0) {
			x->neighbours=(int*)malloc(sizeof(int)*2);
			x->cap=2;
		}
		else {
			x->neighbours=(int*)realloc(x->neighbours,sizeof(int)*2*x->cap);
			x->cap=2*x->cap;
		}
	}
	x->neighbours[x->sz++]=v;
}

void fillAdjList(EdgeList *e,AdjList *adj) {
	int i;
	for(i=0;i<MAX_VERTICES;i++) {
		adj[i].sz=adj[i].cap=0;
		adj[i].neighbours=NULL;
	}
	for(i=0;i<(e->sz);i++) {
		addNeighbour(adj,(e->arr)[i].u,(e->arr)[i].v);
	}
}

int indeg[MAX_VERTICES],outdeg[MAX_VERTICES];
int inserted[MAX_VERTICES] ; 

typedef struct node node ;
struct node {
    int val ; node *next ; 
};
struct list {
    node *head , *tail ;
    int size ; 
};

node* newNode(int temp) {
    node* res = (node*) malloc(sizeof(node)) ;
    res->val = temp ; 
    res->next = NULL ; return res ;
}

list* insert(list* l , node* n) {
    if(l->size == 0) {
        l->size = 1 ; 
        l->head = l->tail = n ; 
        return l ; 
    }
    l->tail->next = n ; 
    l->tail = n; 
    l->size++ ; 
    return l; 
}

// toposort with edge list representation 
// naive way because heap kon implement karega be 
list* toposort1(EdgeList* e) {
    list* res = (list*) malloc(sizeof(list)) ; 
    list->head = list->tail = NULL ; 
    list->size = 0 ; 
    int esize = e->sz ;
    int i ; 
    memset(inserted , 0 , sizeof(inserted)) ; 
    while(1) {
        int found = 0 ; 
        int temp = 0 ; 
        for(i = 0 ; i < esize ; ++i) {
            int u = e->arr[i].u ; 
            int v = e->arr[i].v ;
            if(indeg[u] == 0 && !inserted[u]) {
                temp = u ; found = 1 ; break ;  
            }
            // this can happen , since we dont delete edges 
            // particularly when u is already in the toposort
            if(indeg[v] == 0 && !inserted[v]) {
                temp = v ; found = 1 ; break ;  
            }
        }
        if(!found) break ;
        inserted[temp] = 1 ; 
        node* new_node = newNode(temp) ; 
        res = insert(res , new_node) ;
        for(i = 0 ; i < esize ; ++i) {
            int u = e->arr[i].u , v = e->arr[i].v ; 
            if(u == temp) {
                --indeg[v] ;  
            }
        }
    }
    return res ; 
}

// toposort with adj list implementation 
list* toposort2(AdjList* adj) {
    list* res = (list*) malloc(sizeof(list)) ; 
    list->head = list->tail = NULL ; 
    list->size = 0 ; 
    memset(inserted , 0 , sizeof(inserted)) ; 
    int i; 
    while(1) {
        int found = 0 ; 
        for(i = 0 ; i < MAX_VERTICES ; ++i) {
            if(indeg[i] == 0 && !inserted[i]) {
                found = 1 ; 
                res = insert(res , newNode(i)) ;
                inserted[i] = 1 ; 
                AdjList* l = adj + i ; 
                int j ;
                for(j = 0 ; j < l->sz ; ++j) {
                    int v = l->neighbours[j] ;
                    --indeg[v] ;
                }
                break ; 
            }
        }
        if(!found) break ; 
    }
    return res ;
}
int main() {
	EdgeList *e = createEdgeList(FNAME);
	AdjList adj[MAX_VERTICES];
	fillAdjList(e,adj);
			
	/*
	int i,j;
	for(i=0;i<MAX_VERTICES;i++) if(adj[i].sz){
		printf("%d -",i);
		for(j=0;j<adj[i].sz;j++) {
			printf(" %d",adj[i].neighbours[j]);
		}
		printf("\n");
	}
	*/
	int i;
	memset(indeg,0,sizeof(indeg));
	memset(outdeg,0,sizeof(outdeg));
	for(i=0;i<e->sz;i++) {
		outdeg[(e->arr)[i].u]++;
		indeg[(e->arr)[i].v]++;
    }
    // too lazy to test anything 
	return 0;
}
