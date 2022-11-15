// Linked list implementation ... COMP9024 20T2
#include "list.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXLENGTH 32 //32 for length of name
typedef struct Node {
    int indexOfBUs;
    int time;
    int ordinal;
    char output[MAXLENGTH];
    struct Node *next;
} Node;

List newList() {
    return NULL;
}

Node *makeNode(int indexOfBUs,int ordinal, int time, char *output) {
    Node *new = malloc(sizeof(Node));
    assert(new != NULL);
    new->indexOfBUs = indexOfBUs;
    new->time = time;
    new->ordinal = ordinal;
    strcpy(new->output, output);
    new->next = NULL;
    return new;
}

List insertLL(List L, int indexOfBUs,int ordinal, int time, char *output) {
//    if (inLL(L, flag, timeThreshold , output))
//        return L;

    // add new node at the beginning
    Node *new = makeNode(indexOfBUs,ordinal, time, output);
    new->next = L;
    return new;
}

List deleteLLAElementFromHead(List L) {
    if (L == NULL)
        return L;
    List temp = L->next;
    free(L);

    return temp;

}

bool inLL(List L, int indexOfBUs,int ordinal, int time, char *output) {
    if (L == NULL)
        return false;
    if (L->ordinal == ordinal && L->indexOfBUs == indexOfBUs)
        return true;

    return inLL(L->next, indexOfBUs,ordinal, time, output);
}

void showLL(List L) {
    if (L == NULL)
        return;
    else {
        showLL(L->next);
        if (L->next && L->indexOfBUs != L->next->indexOfBUs)
            printf("Change at %s\n", L->next->output);
        printf("%04d %s\n", L->time, L->output);

    }
}

List copyLL(List L1, List L2) {
    if (L1 != NULL) {
        L2 = copyLL(L1->next, L2);
        L2 = insertLL(L2, L1->indexOfBUs,L1->ordinal, L1->time, L1->output);
    }
    return L2;
}
bool valid(List L) {
    return (L == NULL);
}

List getTheNextNode(List L) {
    return L->next;
}

int getIndexOfBus(List L) {
    return L->indexOfBUs;
}

int getTime(List L) {
    return L->time;
}

char *getOutPut(List L) {
    return L->output;
}
int getOrdinal(List L){
    return L->ordinal;
}

//void insertAfterCertainValue(List L, int bus1, int time1, char *output, int bus2, int time2, char *output2) {
//    while (L != NULL) {
//        if (L->indexOfBUs == bus1 && L->time == time1 && strcmp(L->output, output) == 0) {
//            Node *new = makeNode(bus2, time2, output2);
//            new->next = L->next;
//            L->next = new;
//        }
//        L = L->next;
//    }
//}
void setNextNode(List L,List temp){
    L->next = temp;
}
void freeLL(List L) {
    if (L != NULL) {
        freeLL(L->next);
        free(L);
    }
}
