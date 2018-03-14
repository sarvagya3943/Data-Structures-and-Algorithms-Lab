#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#define filename "aliceinwonderland.txt"

// returns 1 if the character is lower-case english letter 
int isLower(char c) {
    return c >= 'a' && c <= 'z' ;
}

// returns 1 if the character is upper-case english letter 
int isUpper(char c) {
    return c >= 'A' && c <= 'Z' ;
}

/*
 Exercise 1(a) : Hash Function
 */
int get_hash(char* str , int baseNumber , int tableSize) {
    int length = strlen(str) ; 
    int i , hash = 0 ; 
    for(i = 0 ; i < length ; ++i) {
        hash = (hash + str[i]) % baseNumber ; 
    }
    return hash % tableSize ;
}

/*
 Exercise 1(b) : Collision Count
 */
int get_collision(char** arr , int size , int baseNumber , int tableSize) {
    int i , table[tableSize] ; 
    for(i = 0 ; i < tableSize ; ++i) table[i] = 0 ; 
    for(i = 0 ; i < size ; ++i) {
        int hash = get_hash(arr[i] , baseNumber , tableSize) ;
        table[hash] += 1 ; 
    }
    int collision = 0 ; 
    for(i = 0 ; i < tableSize ; ++i) {
        collision += table[i] - 1 ;  
    }
    return collision ; 
}

/*
 Exercise 1(c) : Parsing
 Parse "Filename" and store the strings in arr 
 Returns the total items found. 
 */
int parseFile(char*** arr) {
    FILE *ptr = fopen(filename,"r") ;
    int valid_strings = 0 ; 
    char buffer[1000] ; 
    while(!feof(ptr)) {
        fscanf(ptr , "%[^ ] " , buffer) ;
        int buffLen = strlen(buffer) , i , isValid = 1 ; 
        for(i = 0 ; i < buffLen ; ++i) {
            if(!isLower(buffer[i]) && !isUpper(buffer[i])) {
                isValid = 0 ; break ;  
            }
        }
        if(isValid && buffLen > 0) ++valid_strings ;
    }
    *arr = (char**) malloc(sizeof(char*) * valid_strings) ;
    ptr = fopen(filename , "r") ;
    int index = 0 ; 
    while(!feof(ptr)) {
        fscanf(ptr , "%[^ ] " , buffer) ;
        int buffLen = strlen(buffer) , i , isValid = 1 ; 
        for(i = 0 ; i < buffLen ; ++i) {
            if(!isLower(buffer[i]) && !isUpper(buffer[i])) {
                isValid = 0 ; break ;  
            }
        }
        if(isValid && buffLen > 0) {
            (*arr)[index] = (char*) malloc(buffLen) ; 
            memcpy((*arr)[index++] , buffer , buffLen + 1) ;
        }
    }
    return valid_strings ;
}

/*
 Exercise 1(d) : Profiling 
 */
void profiling(char** arr , int arr_size , int *best_baseNumber , int *best_tableLength) {
    int i , j , baseNumbers[] = {83 , 89 , 97 , 1000003 , 1000033 , 1000037} ; 
    int tableLengths[] = {50 , 100 , 500} ;
    int min_collisions = -1 ; 
    for(i = 0 ; i < 6 ; ++i) {
        for(j = 0 ; j < 3 ; ++j) {
            int collisions = get_collision(arr , arr_size , baseNumbers[i] , tableLengths[j]) ; 
            printf("baseNumber : %d , tableLength : %d , col : %d\n" , baseNumbers[i] , tableLengths[j] , collisions) ;
            if(min_collisions == -1) {
                min_collisions = collisions ;
                *best_baseNumber = baseNumbers[i] ; 
                *best_tableLength = tableLengths[j] ;
            }
            else if(collisions < min_collisions) {
                min_collisions = collisions ; 
                *best_baseNumber = baseNumbers[i] ; 
                *best_tableLength = tableLengths[j] ;
            }
        }
    }
    printf("Minimum collisions are : %d , Best baseNumber is : %d and best tableLength is : %d\n" , min_collisions , *best_baseNumber , *best_tableLength) ; 
    return ;
}

typedef struct node node ; 
typedef struct hash_table hash_table ;


struct node {
    int key ; // stores index of the string
    struct node* next ; // pointer to the next node 
};

node* newNode(int key) {
    node *res = malloc(sizeof(node)) ; 
    res->key = key ; 
    res->next = NULL ; 
    return res ; 
}

struct hash_table {
    int elementCount ; // count of strings stored in the hash table 
    int insertionCost ; // total number of jumps done in any of the lists while inserting(only increment during collisions) 
    int queryingCost ; // total number of comparisons in any chain during lookups 
    struct node** table ; // actual table , table[i] stores pointer to the head of the list i.  
    int size ; // table Size 
};

/*
 Exercise 2(a) : Creation 
 */
hash_table* create_new_hash_table(int tableSize) {
    int i ; 
    hash_table* res = NULL ; 
    res = (hash_table*) malloc(sizeof(hash_table)) ;
    res->table = malloc(sizeof(node*) * tableSize) ; 
    for(i = 0 ; i < tableSize ; ++i) {
        res->table[i] = NULL ;  
    }
    res->elementCount = 0 ; 
    res->insertionCost = res->queryingCost = 0 ; 
    res->size = tableSize ; 
    return res ; 
}

/*
 Exercise 2(b) : Insert
 */
void Insert(hash_table** HashTable , char** arr , int index , int baseNumber) {
    int hash = get_hash(arr[index] , baseNumber , (*HashTable)->size) ;
    node* newnode = newNode(index) ;
    if((*HashTable)->table[hash] == NULL) {
         // first node in the list , no collision 
        (*HashTable)->table[hash] = newnode ; 
    }
    else {
        // collision , insert at end of the list 
        node* head = (*HashTable)->table[hash] ;
        while(head && head->next != NULL) {
            head = head->next ;
            (*HashTable)->insertionCost += 1 ; 
        }
        head->next = newnode ;
    }
    (*HashTable)->elementCount += 1 ; 
    return ;
}

/*
 Exercise 2(c) : InsertAll 
 */
int InsertAll(hash_table** HashTable , char** arr , int arr_size , int baseNumber) {
    int i ; 
    for(i = 0 ; i < arr_size ; ++i) {
        Insert(HashTable , arr , i , baseNumber) ; 
    }
    return (*HashTable)->insertionCost ;
}

/*
 Exercise 2(d) : Lookup
 */
int Lookup(hash_table* HashTable , char** arr , char* string , int baseNumber) {
    int queryCost = 0 ; 
    int hash = get_hash(string , baseNumber , HashTable->size) ;
    node* head = HashTable->table[hash] ; 
    while(head != NULL) {
        int isDifferent = strcmp(arr[head->key] , string) ;
        ++queryCost ; 
        if(!isDifferent) {
            // found the string
            return queryCost ; 
        }
        head = head->next ; 
    }
    return -queryCost ; // couldnt find the string! 
}

/*
 Exercise 2(e) : LookupAll 
 */
int LookupAll(hash_table* HashTable , char** arr , int arr_size , int baseNumber , double m) {
    int queryCost = 0 ; 
    int i , index = (m * arr_size);
    for(i = 0 ; i < index ; ++i) {
        int cost = Lookup(HashTable , arr , arr[i % arr_size] , baseNumber) ;
        queryCost += cost ; 
    }
    return queryCost ;
}

/*
 Exercise 3(a) : Profiling 
 */
double Profiling(hash_table* HashTable , char** arr , int arr_size , int baseNumber) {
    double m = 0.10 ; 
    for( ; m < 10.20 ; m += 0.10) {
        int cost = LookupAll(HashTable , arr , arr_size , baseNumber , m) ; 
        if(cost > HashTable->insertionCost) return m ; 
    }
    return -1.0 ;
}

/*
 Exercise 3(b) : Cleanup 
 */
hash_table* cleanup(hash_table* HashTable , char** arr , int baseNumber) {
    hash_table* res = create_new_hash_table(HashTable->size) ;
    int i = 0 ; 
    for( ; i < HashTable->size ; ++i) {
        node* head = HashTable->table[i] ;
        while(head != NULL) {
            int found = Lookup(res, arr , arr[head->key] , baseNumber) ;
            res->insertionCost += (found < 0 ? -found : found) ;
            if(found <= 0) {
                // doesnt exist , safe to insert 
                Insert(&res , arr , head->key , baseNumber) ;
            }
            head = head->next ; 
        }
    }
    return res ; 
}

void print_table(hash_table* arr) {
    printf("Element count is %d\n" , arr->elementCount) ; 
    printf("Insertion cost is %d\n" , arr->insertionCost) ;
    int i , size = arr->size ; 
    /*for(i = 0 ; i < size ; ++i) {
        if(arr->table[i] != NULL) {
            printf("hash is : %d -> " , i) ;
            node* bla = arr->table[i] ; 
            while(bla != NULL) {
                printf("%d : " , bla->key) ;
                bla = bla->next ;
            }
            printf("\n") ;
        }
    }*/
    return ; 
}
int main() {
    char** book ; 
    int j , i , book_size = parseFile(&book) ;
    printf("%d strings found\n",book_size) ;
    int best_baseNumber = 0, best_tableLength = 0 ; 
    profiling(book , book_size , &best_baseNumber , &best_tableLength) ;
    printf("%d %d\n" , best_baseNumber , best_tableLength) ;
    printf("BEFORE CLEANUP---------\n") ; 
    hash_table* HashTable = create_new_hash_table(best_tableLength) ;
    int cost = InsertAll(&HashTable,book,book_size,best_baseNumber) ;
    printf("Cost is %d\n" , cost) ; 
    double percent = Profiling(HashTable,book,book_size,best_baseNumber) ; 
    printf("Percent is %f\n" , percent*100) ; 
    print_table(HashTable) ; 
    printf("AFTER CLEANUP-----------\n") ; 
    HashTable = cleanup(HashTable , book , best_baseNumber) ;
    percent = Profiling(HashTable , book , book_size , best_baseNumber) ;
    print_table(HashTable) ;
    printf("Insertion Cost : %d , percent is : %f\n" , HashTable->insertionCost , percent*100) ;
    return 0 ; 
}
