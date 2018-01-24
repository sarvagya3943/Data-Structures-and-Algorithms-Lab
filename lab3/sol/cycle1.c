#include "cycle.h" 

int testCyclic(pnode list) {
	// not cyclic , if the list is empty 
	if(list == NULL) return 0 ; 
	pnode hare = list , tort = list ; 
	while(1) {
		if(hare == NULL) break ; // no cycle 
		hare = hare->next ; 
		if(hare == NULL) break ; // no cycle 
		hare = hare->next ; 
		tort = tort->next ;	 
		if(hare == tort) return 1 ; // found cycle 
	}
	return 0 ;
}
