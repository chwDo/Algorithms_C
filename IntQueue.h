//
// Created by 蔡昊文 on 9/6/20.
//

#ifndef INC_9024_C_PROJECT_INTQUEUE_H
#define INC_9024_C_PROJECT_INTQUEUE_H

#endif //INC_9024_C_PROJECT_INTQUEUE_H
// Integer Queue ADO header file ... COMP9024 20T2
#define MAXITEMS 10

void QueueInit();        // set up empty queue
int  QueueIsEmpty();     // check whether queue is empty
void QueueEnqueue(int);  // insert int at end of queue
int  QueueDequeue();     // remove int from front of queue