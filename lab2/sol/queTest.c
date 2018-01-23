#include <stdio.h> 
#include "que.h" 

int main() {
    int i ; 
    Queue q = newQ() ; 
    for(i = 1 ; i <= 10 ; ++i) {
        Element e = (Element)malloc(sizeof(element)) ;
        e->key = i ; e->next = NULL ; 
        q = addQ(q,e) ; 
    }
    printf("Queue size is %d\n" , lengthQ(q)) ;
    while(isEmptyQ(q) == 0) {
        Element res = front(q) ;
        printf("Element is %d\n",res->key) ;
        q = delQ(q) ;
    }
    return 0;
}
