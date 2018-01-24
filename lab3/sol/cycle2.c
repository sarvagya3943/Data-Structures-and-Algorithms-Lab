#include "cycle.h"

int testCyclic(pnode list) {
	if(list == NULL) return 0 ;
	pnode head = list ;  
	pnode prev = NULL ; 
	pnode curr = list ; 
	pnode next = NULL ; 
	if(curr->next == NULL) return 0 ; 
	while(curr != NULL) {
		next = curr->next ; 
		curr->next = prev ; 
		prev = curr ; 
		curr = next ; 
	}
	return prev == head ;
}
