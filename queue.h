//
// Created by 蔡昊文 on 25/7/20.
//

#ifndef INC_9024_C_PROJECT_QUEUE_H
#define INC_9024_C_PROJECT_QUEUE_H

#endif //INC_9024_C_PROJECT_QUEUE_H
// Queue ADT header file ... COMP9024 20T2

typedef struct QueueRep *queue;

queue newQueue();                  // set up empty queue
void  dropQueue(queue);            // remove unwanted queue
int   QueueIsEmpty(queue);         // check whether queue is empty
void  QueueEnqueue(queue, void *); // insert a pointer at end of queue
void *QueueDequeue(queue);         // remove pointer from front of queue