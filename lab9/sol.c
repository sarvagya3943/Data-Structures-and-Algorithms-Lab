#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
typedef struct Iterator Iterator; 
typedef struct node node ; 
#define MAX_HEIGHT 5

struct Iterator {
	node** arr ;
	int size ; 
	int index ;
	int cap ; 	
};
struct node {
	int val ; 
	Iterator* iter ;
};

int key = 0 ; 

int isFull(Iterator* it) {
	return it->size == it->cap ; 
}

Iterator* createIterator(int sz) {
	Iterator* res ; 
	res->size = 0 ; 
	res->index = 0 ; 
	res->arr = (node **) malloc(sizeof(node*) * sz) ;
	int i ;  
	for(i = 0 ; i < sz ; ++i) res->arr[i] = NULL ; 
	res->cap = sz ;
	return res ; 
}

int hasMoreElements(Iterator* it) {
	return it->index < it->size ; 
}

node* getNextElement(Iterator* it) {
	if(hasMoreElements(it)) return it->arr[index++] ;
	return NULL ; 
}


Iterator* AddElement(Iterator* it , node* res) {
	it->arr[it->size++] = res ; 
	return it ;
}

Iterator* resizeIterator(Iterator* it) {
	Iterator* newit = createIterator((it->cap) * 2) ;
	it->index = 0 ; 
	while(hasMoreElements(it)) {
		newit = AddElement(newit , getNextElement(it)) ; 
	}
	return newit ;
}

node* create_node(int height = 0) {
	if(height == MAX_HEIGHT) return ; 
	int children = rand() % 11 ; 
	if(height == MAX_HEIGHT - 1) children = 0 ; 
	node* root = (node*) malloc(sizeof(node)) ; 
	root->val = key++ ; 
	root->iter = createIterator(children) ;
	int temp = children ; 	
	while(temp--) {
		if(isFull(root->iter)) {
			root->iter = resizeIterator(root->iter) ;
		}
		root->iter = AddElement(root->iter , create_node(height + 1)) ;
	}
	return root ;
}

int isEmptyTree(node* root) {
	return root->iter->size != 0 ;
}

int getRootVal(node* root) {
	assert(root != NULL) ; 
	return root->val ; 
}

Iterator* getChildren(node* root) {
	return root->iter ;
}

// DFT and BFT 

int main() {



	return 0 ;
}
