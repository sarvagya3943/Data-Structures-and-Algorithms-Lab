#include "SeqList.h" 
#include <stdio.h> 

SeqList newList() {
    SeqList list = (SeqList)malloc(sizeof(seqList)) ;
    list->size = 0 ; 
    list->front = list->back = NULL ; 
    return list ;
}
SeqList insertAtFront(SeqList sl , Element e) {
    if(sl == NULL) sl = newList() ; 
    if(sl->size == 0) {
        sl->front = sl->back = e ; 
        sl->size = 1 ; 
        return sl ; 
    }
    e->next = sl->front ; 
    sl->front = e ; 
    sl->size++ ;
    return sl ;
}
SeqList insertAtEnd(SeqList sl , Element e) {
    if(sl == NULL) sl = newList() ; 
    if(sl->size == 0) {
        sl->front = sl->back = e ; 
        sl->size = 1 ; 
        return sl ;
    }
    e->next = NULL ; 
    sl->back->next = e ; 
    sl->back = e ; 
    sl->size++ ; 
    return sl ;
}
SeqList insertInOrder(SeqList sl , Element e) {
    if(sl == NULL) sl = newList() ;
    if(sl->size == 0) {
        sl->front = sl->back = e ; 
        sl->size = 1 ; 
        return sl ;
    }
    if(e->key <= sl->front->key) {
       return insertAtFront(sl,e) ;
    }
    if(e->key >= sl->back->key) {
        return insertAtEnd(sl,e) ;
    }
    Element curr = sl->front ; 
    for(;;) {
        if(e->key <= curr->next->key) break ; 
        curr = curr->next ; 
    }
    e->next = curr->next ; 
    curr->next = e ; 
    sl->size++ ; 
    return sl ;
}
SeqList deleteAtFront(SeqList sl) {
    if(sl == NULL || sl->size == 0) return sl ; 
    if(sl->size == 1) {
        sl->size-- ; 
        sl->front = sl->back = NULL ; 
        return sl ;
    }
    Element curr = sl->front ; 
    sl->front = curr->next ; 
    sl->size-- ; 
    free(curr) ;
    return sl ;
}
SeqList delete(SeqList sl , Element e) {
    if(sl == NULL || sl->size == 0) return sl ;
    if(e->key == sl->front->key) return deleteAtFront(sl) ;
    Element prev , temp = sl->front ; 
    while(temp != NULL && temp->key != e->key) {
        prev = temp ; 
        temp = temp->next ; 
    }
    if(temp == NULL) return sl ; 
    prev->next = temp->next ; 
    free(temp) ;
    sl->size-- ; 
    return sl ;
}
Element find(SeqList sl , int key) {
    if(sl == NULL) return NULL ; 
    Element temp = sl->front ; 
    while(temp != NULL && temp->key != key) temp = temp->next ;
    return temp ;
}
void print(SeqList sl) {
    if(sl == NULL) return ; 
    SeqList copy = sl ; 
    Element curr = copy->front ;
    printf("The list is = ") ;
    while(curr != NULL) {
        printf("%d " , curr->key) ;
        curr = curr->next ; 
    }
    printf("\n") ;
}
// can modify the original lists 
// allocate new nodes everytime if that is not allowed
SeqList merge(SeqList sla , SeqList slb) {
    SeqList res = newList() ;
    Element curra = (sla == NULL) ? NULL : sla->front ; 
    Element currb = (slb == NULL) ? NULL : slb->front ;
    while(curra && currb) {
        if(curra->key <= currb->key) {
            Element temp = curra->next ; 
            res = insertAtEnd(res , curra) ; 
            curra = temp ; 
        }
        else {
            Element temp = currb->next ; 
            res = insertAtEnd(res , currb) ; 
            currb = temp ; 
        }
    }
    while(curra) {
        Element temp = curra->next ; 
        res = insertAtEnd(res , curra) ; 
        curra = temp ; 
    }
    while(currb) {
        Element temp = currb->next ; 
        res = insertAtEnd(res , currb) ;
        currb = temp ; 
    }
    return res ; 
}

SeqList insertionSort(SeqList a) {
    SeqList res = newList() ; 
    if(a == NULL || a->size < 2) return a ; 
    Element curr = a->front ; 
    while(curr != NULL) {
        Element next = curr->next ; 
        res = insertInOrder(res , curr) ; 
        curr = next ; 
    }
    return res ; 
}
