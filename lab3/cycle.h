#include <stdio.h>

struct node {
	int data ; 
	struct node* next ; 
};

typedef struct node node ;
typedef node* pnode ;


int testCyclic(pnode list) ;
