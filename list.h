//
// Created by 蔡昊文 on 3/7/20.
//

#ifndef INC_9024_C_PROJECT_LIST_H
#define INC_9024_C_PROJECT_LIST_H

#endif //INC_9024_C_PROJECT_LIST_H
// Linked list interface ... COMP9024 20T2
#include <stdbool.h>

typedef struct Node *List;

List newList();
List insertLL(List,int, int ,int ,char *);
//void insertAfterCertainValue(List, int ,int ,char *,int ,int ,char *);
List deleteLLAElementFromHead(List);
bool inLL(List, int, int ,int ,char *);
void freeLL(List);
void showLL(List);
List copyLL(List,List);
bool valid(List);
List getTheNextNode(List);
int getIndexOfBus(List);
void setNextNode(List,List);
int getTime(List);
char* getOutPut(List);
int getOrdinal(List);