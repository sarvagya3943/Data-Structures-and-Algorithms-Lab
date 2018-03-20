#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

typedef struct node node ; 

struct node {
	int val ; 
	node *left , *right ;
	int bal ; 	
	int count ; 
}; 

node* new_node(int key) {
	node* res = (node*) malloc(sizeof(node)) ; 
	res->val = key ; res->count = 1 ; 
	res->left = res->right = NULL ; res->bal = 0 ; return res ;
}

int get_num() {
	return (rand() % 21) + 150 ; 
}

int get_count(node* root) {
	return (root == NULL) ? 0 : root->count ; 
}

node* add(node* root , int key) {
	if(root == NULL) return new_node(key) ; 
	if(key <= root->val) {
		root->left = add(root->left , key) ; 
	}
	else root->right = add(root->right , key) ;
	root->count = get_count(root->left) + get_count(root->right) + 1 ;  
	return root ;
}

node* find(node* root, int key) {
	if(root == NULL || key == root->val) return NULL ; 
	if(key < root->val) return find(root->left , key) ; 
	return find(root->right , key) ;
}

node* delete(node* root , int key) {
	if(root == NULL) return root ; 
	if(key < root->val) root->left = delete(root->left , key) ; 
	else if(key > root->val) root->right = delete(root->right , key) ;
	else {
		if(root->left == NULL) {
			node* temp = root->right ; 
			free(root) ; 
			return temp ;
		}
		else if(root->right == NULL) {
			node* temp = root->left ; 
			free(root) ; return temp ; 
		}
		else {
			node* current = root->right ; 
			while(current->left != NULL) current = current->left ; 
			root->val = current->val ; 
			root->right = delete(root->right , current->val) ; 
		}		
	}
	root->count = get_count(root->left) + get_count(root->right) + 1 ;  
	return root ; 
}

void inorder(node* root) {
	if(root) {
		inorder(root->left) ; 
		printf("%d " , root->val) ; 
		inorder(root->right) ; 
	}
	return ; 
}

node* inorder(node* root , int k) {
	if(!root || k > get_count(root)) return NULL ; 
	int count_left = get_count(root->left) ; 
	if(k <= count_left) return inorder(root->left , k) ; 
	k -= count_left ; 
	if(k == 1) return root ; 
	k -= 1 ; 
	return inorder(root->right , k) ; 
}

node* nodes[MAX] ; 
int index = 0 ; 
// remember to set index = 0  before calling this function ! You have been warned
void query_range(node* root , int k1 , int k2) {
	if(root == NULL) return ; 
	if(root->val < k1) {
		query_range(root->right,k1,k2) ; return ; 	
	}
	if(root->val > k2) {
		query_range(root->left , k1, k2); return ; 
	}	
	nodes[index++] = root ; 
	query_range(root->left , k1 , x) ; 
	query_range(root->right , x , k2) ; 
}
// functions for balanced BST 
node* rotate(node* root , node* X , node* Y , node* Z, node* parent) {
	node* T0 = X->left ; 
	node* T1 = X->right ; 
	node* T2 = Y->right ;
	node* T3 = Z->right ;
	
}
int main() {
	srand(time(NULL)) ;
	int i ;	
	node* root = NULL ; 
	for(i = 0 ; i < 10000 ; ++i) {
		int key = get_num() ; 
		root = add(root , key) ; 	
	}	
	inorder(root) ;
	printf("----------------------\n") ; 
	for(i = 0 ; i < 10000 ; ++i) {
		root = delete(root , 150) ; 	
	}
	inorder(root) ; 
	return 0 ; 
}
