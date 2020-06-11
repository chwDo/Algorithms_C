//
// Created by 蔡昊文 on 9/6/20.
//

#include "IntStack.h"
#include <assert.h>

typedef struct {
    int item[MAXITEMS];
    int top;
}stackRep;

static stackRep stackObject;

void StackInit() {
    stackObject.top = -1;
}     // set up empty stack

int  StackIsEmpty() {
    return (stackObject.top < 0);
}  // check whether stack is empty

void StackPush(int n) {
    assert(stackObject.top < MAXITEMS-1);
    stackObject.top++;
    stackObject.item[stackObject.top] = n;
}

int  StackPop() {
    assert(!StackIsEmpty());
    int n;
    n = stackObject.item[stackObject.top];
    stackObject.top--;
    return n;
}