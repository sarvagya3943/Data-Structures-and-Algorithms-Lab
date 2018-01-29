#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
#include "cycle.h"

int totalMem = 0 ; 

void* myalloc(int size , int count) {
	void* new = (void*) malloc(size*count) ; 
	totalMem += (size * count) ; 
	return new ; 	
}

void myfree(void** ptr , int count , int size) {
	totalMem -= (size * count) ; 
	free(*ptr); return ;
}

pnode newNode() {
	void* mem = myalloc(sizeof(node),1) ;
	return (node*) mem ;
} 

void delNode(pnode temp) {
	void* ptr = temp ; 
	myfree(&ptr , 1 , sizeof(node)) ; 
	return ; 
}
pnode createList(int N) {
	int i = 0 ; 
	int temp = totalMem ; 
	pnode head = newNode() ; 
	head->data = rand() ; 
	head->next = NULL ; 
	pnode curr = head ; 
	for(i = 1 ; i < N ; ++i) {
		pnode new = newNode() ; 
		new->data = rand() ; 
		new->next = NULL ; 
		curr->next = new ; 
		curr = curr->next ; 
	}
	printf("Total memory allocated is %d\n",totalMem-temp);
	return head ; 		
}

pnode createCycle(pnode list) {
	if(list == NULL) return list ; 
	int coinToss = rand() % 2 ;
	if(coinToss == 1) {
		int size = 1 ; 
		pnode last = list ; 
		while(last->next != NULL) {
			last = last->next ; 
			++size ; 	
		}
		int r = rand() % size ; 
		int counter = 0 ;
		pnode curr = list ;  
		while(counter < r) {
			curr = curr->next ; 
			++counter ; 
		}
		last->next = curr ; 
	} 
	return list ;
}

pnode makeCircularList(pnode list) {
	int isCyclic = testCyclic(list) ; 
	if(isCyclic) {
		pnode head = list , hare = list , tort = list ; 
		while(1) {
			if(hare->next == NULL) break ; 
			hare = hare->next ; 
			if(hare->next == NULL) break ; 
			hare = hare->next ; 
			tort = tort->next ; 
			if(hare == tort) {
				while(head != hare) {
					pnode temp = head->next ; 
					delNode(head) ; 
					head = temp ; 
					hare = hare->next ; 
				}
				return head ; 
			}
		}
	}
	else {
		pnode curr = list ; 
		while(curr->next) curr = curr->next ;
		curr->next = list ;	
	}
	return list ;
}
int main() {
	srand(time(0));
	printf("Enter the size of the list : ");
	int N ; 
	scanf("%d",&N) ; 
    struct timeval t1,t2 ; 
    double elapsedTime ; 
    gettimeofday(&t1,NULL) ;
	pnode list = createList(N) ;
	list = createCycle(list) ;
	int isCyclic = testCyclic(list) ;
    gettimeofday(&t2,NULL) ;
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0 ; 
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0 ; 
	if(isCyclic) printf("List has a cycle\n");
	else printf("List is linear\n");
    printf("Total time taken is %f ms\n" , elapsedTime) ;
	return 0;
}
