#include <stdio.h>
#include "element.h"
#define FILE_SMALL "1024.txt"
#define FILE_BIG "10240.txt"

void merge(Element Ls1[] , int sz1 , Element Ls2[] , int sz2 , Element Ls[]) {
	int i = 0 , j = 0 ; 
	int k = 0 ; 
	while(i < sz1 && j < sz2) {
		if(Ls1[i].cgpa < Ls2[j].cgpa) Ls[k++] = Ls1[i++] ;
		else Ls[k++] = Ls2[j++] ; 
	}
	while(i < sz1) Ls[k++] = Ls1[i++] ; 
	while(j < sz2) Ls[k++] = Ls2[j++] ; 
	return ;
}

void recursive_merge_sort(Element arr[] , int sz) {
	if(sz < 2) return ; 
	Element Left[sz/2] , Right[sz-sz/2] ;
	int j = -1 , k = -1 , i = 0 ;  
	for(i = 0 ; i < sz ; ++i) {
		if(i < sz/2) Left[++j] = arr[i] ; 
		else Right[++k] = arr[i] ; 
	}
	recursive_merge_sort(Left,sz/2) ; 
	recursive_merge_sort(Right,sz-sz/2) ;
	merge(Left,sz/2,Right,sz-sz/2,arr) ;
}

void iterative_merge_sort(Element arr[] , int sz) {
	int x,i,group_size = 1 ; 
	while(group_size < sz) {
		for(i = 0 ; i < sz - 1 ; i += group_size*2) {
			int ii = i + group_size - 1 ; 
            if(ii > sz - 1) ii = sz - 1 ; 
			int j = ii + 1 ; 
			int jj = j + group_size - 1 ; 
			if(jj > sz - 1) jj = sz - 1 ; 
			int total_size = ii - i + 1 + jj - j + 1 ; 
            Element buffer[total_size] ;
			merge(arr + i , ii - i + 1 , arr + j , jj - j + 1 , buffer) ; 
			for(x = 0 ; x < total_size ; ++x) {
				arr[i + x] = buffer[x] ; 
			}
	    }
		group_size *= 2 ;
	}
}

int count_entries(FILE* ptr) {
	int ans = 0 ; 
	char buf[15] ; 
	float temp ; 
	while(!feof(ptr)) {
		fscanf(ptr,"%[^,],%f\n",buf,&temp);	
		++ans ; 
	}
	return ans ;
}
// read count items and store in arr
// assumes there are 'count' entries present already  
FILE* read_stuff(FILE* ptr , Element arr[] , int count) {
	int index = 0 ; 
	while(index < count) {
		fscanf(ptr,"%[^,],%f\n",arr[index].Name , &arr[index].cgpa) ;
		printf("%s %d\n",arr[index].Name , index) ;
		++index ; 
	}
	return ptr ;
}
int main() {
	FILE *ptr = fopen("10240.txt","r") ;
	if(ptr == NULL) {
		printf("Cant read file !!!!") ; 
		exit(0) ; 
	} 
	int sz = 0 ; 
	char buff[25] ; 
	float temp ; 
	while(!feof(ptr)) {
		fscanf(ptr,"%[^,],%f\n",buff,&temp) ;
		sz++ ; 
	}
	ptr = fopen("10240.txt","r") ;
	Element arr[sz] ; 
	int index = 0 ; 
	while(!feof(ptr)) {
		fscanf(ptr,"%[^,],%f\n",arr[index].Name,&arr[index].cgpa);	
		++index ; 
	}
	iterative_merge_sort(arr,sz);
	for(index = 0 ; index < sz ; ++index) {
		printf("%s %f\n",arr[index].Name , arr[index].cgpa);
	}
    return 0 ; 
}
