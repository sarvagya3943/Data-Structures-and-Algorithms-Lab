#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
struct record {
	long long card_number ;
	char *bank_code ; 
	char *expiry_date ; 
	char *first_name ; 
	char *last_name ; 
};
typedef struct record record;
record *arr ; 
void read() {
	FILE* fp ; 
	char* line = NULL ;
	size_t len = 0 ; 
	fp = fopen("1000" , "r") ;
	int size = 3 ; 	
	arr = (record*) malloc(size * sizeof(record)) ; 
	if(fp == NULL) {
		printf("Error while reading file\n");
		return 0 ; 	
	}
	int count = 0 ; 
	while(getline(&line , &len , fp) != -1) {
		if(count >= size) {
			// need to reallocate 
			size *= 2 ; 
			record *new_arr = (record*) realloc(arr , sizeof(record) * size) ; 
			arr = new_arr ; 	
		}
		// arr[count] is the new record 
		char *token ;
		int idx = 0 ; 
		while(token = strsep(&line, ",")) {
			int len = strlen(token) ; 
			if(idx == 0) {
				// remove "
				long long card_number = atoll(token + 1) ;
				arr[count].card_number = card_number ; 
			}
			else if(idx == 1) {
				arr[count].bank_code = (char*)malloc(sizeof(char) * len) ;
				memcpy(arr[count].bank_code , token , sizeof(token)) ;
			}
			else if(idx == 2) {
				arr[count].expiry_date = (char*)malloc(sizeof(char) * len) ;
				memcpy(arr[count].expiry_date , token , sizeof(token)) ;
			}
			else if(idx == 3) {
				arr[count].first_name = (char*)malloc(sizeof(char) * len) ;
				memcpy(arr[count].first_name , token , sizeof(token)) ;
			}
			else if(idx == 4) {
				arr[count].last_name = (char*)malloc(sizeof(char) * len) ;
				memcpy(arr[count].last_name , token , strlen(token) - 1) ;
				int len = strlen(arr[count].last_name) ;
				arr[count].last_name[len - 1] = '\0' ;
			}
			++idx ; 
		}
		++count ;
	}
	fclose(fp) ;
}	 
int main() {
	read() ;
	return 0 ;
}
