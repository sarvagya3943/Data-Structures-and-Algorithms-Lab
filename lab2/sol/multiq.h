#include <stdlib.h> 
#include "que.h"

struct task {
    int task_id ; 
    int prior ; 
};

typedef struct task task ; 
typedef task* Task ; 

struct multiq {
    Queue *arr ;
    int size ;
};

typedef struct multiq multiq ; 
typedef multiq* MultiQ ; 

MultiQ createMQ(int num);
MultiQ addMQ(MultiQ mq , Task t) ;
Task nextMQ(MultiQ mq) ;
Task delNextMQ(MultiQ mq) ;
Task isEmptyMQ(MultiQ mq) ;
int sizeMQ(MultiQ mq) ;
int sizeMQbyPriority(MultiQ mq , int priority) ;
Queue getQueueFromMQ(MultiQ mq , int priority) ;