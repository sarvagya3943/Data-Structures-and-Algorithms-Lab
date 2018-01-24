#include <stdio.h>

int bits = 0 ; 

void p() {
	int pilani = 0 ; 
	printf("Address for variable pilani = %u\n",&pilani) ;
	return ; 
}
void g() {
	int goa = 0 ; 
	printf("Address for variable goa = %u\n",&goa) ;
	return ; 	
}
void h() {
	int hyd = 0 ; 
	printf("Address for variable hyd = %u\n",&hyd) ;
	return ; 	
}
void d() {
	int dub = 0 ;
 	printf("Address for variable dub = %u\n",&dub) ;
	return ; 	
}
void pnew(int n) {
	printf("Address for n = %d is %u\n",n,&n) ;
	pnew(n + 1) ; 
	return ;
}
int main() {
	printf("Address for variable bits = %u\n",&bits);
	p() ; 
	g() ; 
	h() ; 
	d() ;
	pnew(10);  	
	return 0 ; 
}
