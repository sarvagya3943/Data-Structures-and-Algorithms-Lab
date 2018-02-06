#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long totalMem = 0 ; 

void* myalloc(int size , int count) {
	void* new = (void*) malloc(size*count) ; 
	totalMem += (size * count) ; 
	return new ; 	
}
/* alternate solution 
void* myalloc(int size , int count) {
	totalMem += (size * count) ; 
	void *temp = malloc(size * count + 4) ; 
	*((int*)temp) = count ; return temp + 4 ; 
}
void myfree(void **ptr , int size) {
	totalMem -= (size * *(int*(ptr-4)) ; 
	free(ptr - 4) ; 
}
*/

void myfree(void** ptr , int count , int size) {
	totalMem -= (size * count) ; 
	free(*ptr); return ;
}

int main() {
	srand(time(NULL)) ;
	int iteration = 0 ;  
	for(;iteration < 20;) {
		int m = rand() % 15001 + 10000 ; 
		printf("Size is %d\n",m);  
		void* mem = myalloc(sizeof(int),m) ;
		int* A = (int*)mem ; 
		if(mem == NULL) break ; 
		printf("address of first element = %u and address of last element = %u\n" , A , &(A[m-1])) ;
		printf("Total memory is %lld\n" , totalMem) ;
		myfree(&mem,m,sizeof(int)) ; 		
		iteration += 1 ;	
	}
	printf("Total iterations were %d\n" , iteration) ;	
	
	return 0 ; 
}
