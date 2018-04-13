#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FNAME "graph0.txt"
#define MAX_VERTICES 100

typedef struct Edge Edge;
typedef struct EdgeList EdgeList;
typedef struct AdjList AdjList;

struct Edge{
	int u,v;
};

Edge makeEdge(int u,int v) {
	Edge x=(Edge)malloc(sizeof(Edge));
	x->u=u;
	x->v=v;
	return *x;
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
	EdgeList e = (EdgeList)malloc(sizeof(EdgeList));
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
	return 0;
}
