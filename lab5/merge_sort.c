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
	FILE *ptr = fopen("1024.txt","r") ;
	if(ptr == NULL) {
		printf("Cant read file !!!!") ; 
		eixt(0) ; 
	} 
	int sz = 0 ; 
	char buff[25] ; 
	float temp ; 
	while(!feof(ptr)) {
		fscanf(ptr,"%[^,],%f\n",buff,&temp) ;
		sz++ ; 
	}
	ptr = fopen("1024.txt","r") ;
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
	
// THIS IS NOT RIGHT YET , PROCEED AT YOUR OWN RISK

	/*FILE* ptr_big = fopen(FILE_BIG,"r");
	if(ptr_big == NULL) {
		printf("Cant read the file\n") ; 
		exit(0);
	}
	int total_entries = count_entries(ptr_big) ; 
	Element arr1[total_entries/2] ; 
	Element arr2[total_entries - total_entries/2] ;
	ptr_big = read_stuff(ptr_big , arr1 , total_entries/2) ; 
	//recursive_merge_sort(arr1 , total_entries) ; 
	int i = 0 ; 
	for(i = 0 ; i < total_entries/2 ; ++i) {
	//	printf("%s %f\n" , arr1[i].Name , arr1[i].cgpa) ; 
	}
	FILE* file1 = fopen("array1.txt","w") ; 
	if(file1 == NULL) {
		printf("Cant write to file\n"); exit(0) ; 
	}
	int index = 0 ; 
	while(index < total_entries/2) {
		printf("%s %f\n" , arr1[index].Name , arr1[index].cgpa) ; 
		fprintf(file1,"%s %f\n",arr1[index].Name,arr1[index].cgpa); index++ ; 
	}
	ptr_big = read_stuff(ptr_big , arr2 , total_entries - total_entries/2) ;
	recursive_merge_sort(arr2 , total_entries - total_entries/2) ;
	FILE* file2 = fopen("array2.txt","w") ; 
	if(file2 == NULL) {
		printf("Cant write to file\n"); exit(0) ; 
	}
	index = 0 ; 
	while(index < total_entries - total_entries/2) {
		fprintf(file2,"%s %f\n",arr2[index].Name , arr2[index].cgpa) ;
		++index ; 
	}*/
	return 0 ; 
}
