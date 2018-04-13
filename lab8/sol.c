#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#define MAX 10005 
typedef struct node node ; 

int max(int a , int b) {
    return (a > b) ? a : b ; 
}
// part(a) 

struct node {
	int val ; 
	node *left , *right ;
    int height ;
	int count ; // if we cant store this , we can calculate this in O(subtree size) everytime , that'd be stupid though 
}; 

// returns a new node pointer with node val as 'key' 
node* new_node(int key) {
	node* res = (node*) malloc(sizeof(node)) ; 
	res->val = key ; res->count = res->height = 1 ;  
	res->left = res->right = NULL ; return res ;
}

// returns a random number in range [150,170] 
int get_num() {
	return (rand() % 21) + 150 ; 
}

// returns the subtree size of a node in O(1) 
// can be implemented naively in O(subtree size) if we cant store 'count' in node structure
int get_count(node* root) {
	return (root == NULL) ? 0 : root->count ; 
}

node* update_count(node* root) {
    if(root) {
        root->count = get_count(root->left) + get_count(root->right) + 1; 
    }
    return root ; 
}

// returns the height of a node 
int getHeight(node* root) {
    return (root) ? root->height : 0 ; 
}

// self explanatory
node* update_height(node* root) {
    if(root) {
        root->height = max(getHeight(root->left) , getHeight(root->right)) + 1 ;  
    }
    return root ; 
}

node* update_info(node* root) {
    root = update_height(root) ; 
    root = update_count(root) ; 
    return root ; 
}

// returns the balance of a node 
int getBalance(node* root) {
    return (root) ? getHeight(root->right) - getHeight(root->left) : 0 ;
}

// part(b)

// dont call when root has no right child , program will crash :P 
node* get_inorder_successor(node* root) {
    node* curr = root->right ; 
    while(curr->left) curr = curr->left ;
    return curr ;
}

// naive way to get subtree size 
// noobs do this , dont be like them 
/*int get_count(node* root) {
    if(root == NULL) return 0 ; 
    return 1 + get_count(root->left) + get_count(root->right) ;
}*/

// insert function for normal BST(not balanced)
node* add(node* root , int key) {
	if(root == NULL) return new_node(key) ; 
	if(key <= root->val) {
		root->left = add(root->left , key) ; 
	}
	else root->right = add(root->right , key) ;
	root->count = get_count(root->left) + get_count(root->right) + 1 ;  
	return root ;
}

// find function for any BST
node* find(node* root, int key) {
	if(root == NULL || key == root->val) return root ; 
	if(key < root->val) return find(root->left , key) ; 
	return find(root->right , key) ;
}

// delete function for normal BST(not balanced) 
// this was tricky 
node* delete(node* root , int key) {
    // find the node to be deleted first 
	if(root == NULL) return root ; 
	if(key < root->val) root->left = delete(root->left , key) ; 
	else if(key > root->val) root->right = delete(root->right , key) ;
	else {
        // found it 
        // handle nodes with one child 
        // leaves will be handled automatically 
		if(root->left == NULL) {
			node* temp = root->right ; 
			free(root) ; 
			return temp ;
		}
		else if(root->right == NULL) {
			node* temp = root->left ; 
			free(root) ; return temp ; 
		}
        // nodes with 2 children
        // convert this to an easier to handle case(nodes with <= 1 children)
        // replace root with its inorder successor 
        // probably should make a separate function to calculate that but fuck it 
        // call delete on the inorder successor's value and we are done (think why?) 
		else {
			node* current = get_inorder_successor(root) ; 
			root->val = current->val ; 
			root->right = delete(root->right , current->val) ; 
		}		
	}
    root = update_info(root) ; 
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

void preorder(node* root) {
    if(root) {
        printf("%d(%d) " , root->val , getBalance(root)) ; 
        preorder(root->left) ; 
        preorder(root->right) ; 
    }
    return ; 
}
// just for debugging purposes
int get(node* root) {
    return (root) ? root->val : 0 ; 
}

#define trace(x) 
// assumes X,Y,Z to not be NULL otherwise whats the point ? -_- 
node* rotate(node* root , node* X , node* Y , node* Z) {
    if(root == NULL) return root ; // cant rotate empty tree
    else if(Z->val < root->val) root->left = rotate(root->left , X , Y , Z) ;
    else if(Z->val > root->val) root->right = rotate(root->right , X , Y , Z) ; 
    else {
        node *a , *b , *c , *T0 , *T1 , *T2 , *T3 ;  
        if(Z->left == Y) {
             // left-left case 
             if(Y->left == X) {
                a = X , b = Y , c = Z ; 
                T0 = X->left , T1 = X->right , T2 = Y->right , T3 = Z->right ;
             }
             // left-right case 
             else {
                a = Y , b = X , c = Z ; 
                T0 = Y->left , T1 = X->left , T2 = X->right , T3 = Z->right ;
             }
        }
        else {
             // right-left case 
             if(Y->left == X) {
                a = Z , b = X , c = Y ; 
                T0 = Z->left , T1 = X->left , T2 = X->right , T3 = Y->right ;
             }
             // right-right case 
             else {
                a = Z , b = Y , c = X ; 
                T0 = Z->left , T1 = Y->left , T2 = X->left , T3 = X->right ;
             }
        }
        root = b ;
        b->left = a , b->right = c ; 
        a->left = T0 , a->right = T1 , a = update_info(a) ; 
        c->left = T2 , c->right = T3 , c = update_info(c) ;  
    }
    root = update_info(root) ;
    return root ; 
}

// insert function for balanced BST 
node* add_bal(node* root , int key) {
    if(root == NULL) return new_node(key) ;
    if(key <= root->val) root->left = add_bal(root->left , key) ;
    else root->right = add_bal(root->right , key) ;
    root = update_info(root) ;
    int balance = getBalance(root) ;
    if(balance < -1) {
        // left heavy subtree 
        // left-left case 
        if(key <= root->left->val) {
            return root = rotate(root , root->left->left , root->left , root) ;  
        }
        // left right 
        return root = rotate(root , root->left->right , root->left , root) ; 
    }
    else if(balance > 1) {
        // right heavy subtree 
        // right-right case 
        if(key > root->right->val) {
            return root = rotate(root , root->right->right , root->right , root) ;  
        }
        // right-left
        return root = rotate(root , root->right->left , root->right , root) ;
    }
    return root ; 
}

// delete node in balanced BST 
node* delete_bal(node* root , int key) {
    // standard delete kar do pehle 
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
			node* current = get_inorder_successor(root) ; 
			root->val = current->val ; 
			root->right = delete(root->right , current->val) ; 
		}		
	}
    if(root == NULL) return root ; 
    root = update_info(root) ; 
    int balance = getBalance(root) ; 
    if(balance < -1) {
        // left heavy subtree 
        int balance_left = getBalance(root->left) ; 
        // left-left case 
        if(balance_left <= 0) {
            return root = rotate(root , root->left->left , root->left , root) ;  
        }
        // left right 
        return root = rotate(root , root->left->right , root->left , root) ; 
    }
    else if(balance > 1) {
        // right heavy subtree 
        int balance_right = getBalance(root->right) ;
        // right-right case 
        if(balance_right >= 0) {
            return root = rotate(root , root->right->right , root->right , root) ;  
        }
        // right-left
        return root = rotate(root , root->right->left , root->right , root) ;
    }
	return root ; 
}

// rank query 2(a)
// return Kth smallest element in the tree
node* rankQ(node* root , int k) {
	if(!root || k > get_count(root)) return NULL ; 
	int count_left = get_count(root->left) ; 
	if(k <= count_left) return rankQ(root->left , k) ; 
	k -= count_left ; 
	if(k == 1) return root ; 
	k -= 1 ; 
	return rankQ(root->right , k) ; 
}

node* nodes[MAX] ; 
int Index = 0 ; 

// remember to set index = 0  before calling this function ! You have been warned
// nodes[0..index) would be the required stuff 

void query_range(node* root , int k1 , int k2) {
	if(root == NULL) return ; 
	if(root->val < k1) {
		query_range(root->right,k1,k2) ; return ; 	
	}
	if(root->val > k2) {
		query_range(root->left , k1, k2); return ; 
	}	
	nodes[Index++] = root ; 
	query_range(root->left , k1 , root->val) ; 
	query_range(root->right , root->val , k2) ; 
}

int main() {
	srand(time(NULL)) ;
	int i ;	
    node* root = NULL ; 
    // use add and delete for standard BST 
    // use add_bal and delete_bal for balanced BST 
    for(i = 1 ; i < MAX ; ++i) {
        int key = get_num() ;
        root = add_bal(root , key) ; 
    }
    for(i = 100 ; i <= 105 ; ++i) {
        node* res = rankQ(root , i) ; 
        printf("%d " , res->val) ; 
    }
    printf("\n") ; 
    Index = 0 ; 
    query_range(root , 155,155) ; 
    for(i = 0 ; i < Index ; ++i) {
        printf("%d ", nodes[i]->val) ; 
    }
    printf("\n") ;
    return 0 ;
}
