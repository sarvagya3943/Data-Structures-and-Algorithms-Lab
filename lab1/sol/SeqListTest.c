#include <stdio.h> 
#include "SeqList.h" 

int main() {
    int i ; 
    srand(time(NULL)) ; 
    SeqList list = newList() ;
    for(i = 10 ; i >= 0 ; --i) {
        Element e = (Element)malloc(sizeof(element)) ;
        e->key = i ; 
        e->next = NULL ; 
        list = insertAtFront(list , e) ; 
    }
    list = insertionSort(list) ;
    SeqList list2 = newList() ;
    for(i = 21 ; i >= 11 ; --i) {
        Element e = (Element)malloc(sizeof(element)) ;
        e->key = i ; 
        e->next = NULL ; 
        list2 = insertAtFront(list2 , e) ; 
    }
    list2 = insertionSort(list2) ;
    SeqList mergedList = merge(list , list2) ;
    print(mergedList) ;
    return 0 ; 
}
