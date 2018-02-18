#include "ex1.h"

void swap(Emp *a,Emp *b) {
	Emp tmp=*a;
	*a=*b;
	*b=tmp;
}

int partition(Emp e[],int lo,int hi) {
	int i,j,k;

	i=lo-1;
	j=lo;
	k=e[hi].empID;
	for(;j<=hi-1;j++) {
		if(e[j].empID<=k) {
			i++;
			swap(&e[i],&e[j]);
		}
	}
	swap(&e[i+1],&e[hi]);
	return i+1;
}

void InsertionSort(Emp e[],int lo,int hi) {
	int i,j;
	for(i=lo+1;i<=hi;i++)
		for(j=i-1;j>=lo;j--) 
			if(e[j+1].empID < e[j].empID)
				swap(&e[j+1],&e[j]);
}

void QuickSort(Emp e[],int L,int S,int stack[]) {
	int top=-1;
	stack[++top]=0;
	stack[++top]=L-1;
	while(top>=0) {
		int hi=stack[top--];
		int lo=stack[top--];
		
		if(hi-lo+1<S) {
			InsertionSort(e,lo,hi);
			continue;
		}

		int p=partition(e,lo,hi);
		
		if(p-1>lo) {
			stack[++top]=lo;
			stack[++top]=p-1;
		}
		
		if(p+1<hi) {
			stack[++top]=p+1;	
			stack[++top]=hi;
		}
	}
		
}



void Sort(Emp e[],int L,int S,int stack[]) {
	//QuickSort calls InsertionSort
	QuickSort(e,L,S,stack);	
}


