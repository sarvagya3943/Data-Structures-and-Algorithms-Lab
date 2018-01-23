#include "multiq.h" 

MultiQ createMQ(int num) {
	MultiQ res = (MultiQ)malloc(sizeof(multiq)) ;
	res->arr = 
}
MultiQ addMQ(MultiQ mq , Task t) ;
Task nextMQ(MultiQ mq) ;
Task delNextMQ(MultiQ mq) ;
Task isEmptyMQ(MultiQ mq) ;
int sizeMQ(MultiQ mq) ;
int sizeMQbyPriority(MultiQ mq , int priority) ;
Queue getQueueFromMQ(MultiQ mq , int priority) ;