#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Employee {
	char *name;
	int empID;
};

typedef struct Employee Emp;

void swap(Emp *a,Emp *b);

int partition(Emp e[],int lo,int hi);

void QuickSort(Emp e[],int L,int S,int stack[]);

void InsertionSort(Emp e[],int lo,int hi);

void Sort(Emp e[],int L,int S,int stack[]);
