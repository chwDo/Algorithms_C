//
// Created by 蔡昊文 on 9/6/20.
//

#include "IntQueue.h"
#include <assert.h>

typedef struct {
    int item[MAXITEMS];
    int bottom;
    int top;
    int counter;
} intQueueRep;

static intQueueRep intQueueObject;

void QueueInit() {
    intQueueObject.top = 0;
    intQueueObject.bottom = 0;
    intQueueObject.counter = 0;
}        // set up empty queue
int QueueIsEmpty() {
    return (intQueueObject.counter == 0);
}     // check whether queue is empty
void QueueEnqueue(int n) {
    assert(intQueueObject.counter != MAXITEMS);
    intQueueObject.counter++;
    intQueueObject.item[intQueueObject.top] = n;
    intQueueObject.top = (intQueueObject.top + 1) % MAXITEMS;
}  // insert int at end of queue
int QueueDequeue() {
    assert(!QueueIsEmpty());
    intQueueObject.counter--;
    int n;
    n = intQueueObject.item[intQueueObject.bottom];
    intQueueObject.bottom = (intQueueObject.bottom + 1) % MAXITEMS;
    return n;
}     // remove int from front of queue