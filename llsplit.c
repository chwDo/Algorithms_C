
// Created by 蔡昊文 on 18/6/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
typedef struct Node{
    int data;
    struct Node *next;
}NodeT;
void freeLL(NodeT *list) {
        NodeT *p, *temp;
        p = list;
        while (p != NULL) {
            temp = p->next;
            free(p);
            p = temp;
        }
}
NodeT *makeNode(int v) {
    NodeT *new = malloc(sizeof(NodeT));
    assert(new != NULL);
    new->data = v;       // initialise data
    new->next = NULL;    // initialise link to next node
    return new;          // return pointer to new node
}
NodeT *joinLL(NodeT *list, int v){
    while(list->next != NULL){
        list = list->next;
    }
    list->next = makeNode(v);
    return list;
}
void showLL(NodeT *list) {
    NodeT *p;
    printf("Done.");
    if(list !=NULL){
        printf(" List is ");
    }
    for (p = list; p != NULL; p = p->next){
        printf("%d", p->data);
        if(p->next != NULL) {
            printf("-->");
        }
        else{
            printf("\n");
        }
    }
}
void showLLWithTwoPart(NodeT *list,int n){
    printf("First part is ");
    int i;
    NodeT *p;
    // display first part
    for(i = 0,p = list;i< (n-1)/2+1;i++,p = p->next){  //(n-1)/2+1; present floor n/2
        printf("%d", p->data);
        if(i !=(n-1)/2){
            printf("-->");
        }
        else{
            printf("\n");
        }
    }
    //display second part;
    if(n >= 2){
        printf("Second part is ");
        for(i = (n-1)/2+1;i< n;i++,p = p->next){  //(n-1)/2+1; present floor n/2
            printf("%d", p->data);
            if(i != n - 1){
                printf("-->");
            }
            else{
                printf("\n");
            }
        }
    }
}
int main(int argc,char *argv[]) {
    NodeT *all=makeNode(0);
    int v;
    int length = 0;  //record length of list at input
    printf("Enter an integer: ");
    while(scanf("%d",&v)){
        length ++;
        printf("Enter an integer: ");
        joinLL(all,v);
    }
    showLL(all->next);
    if(all->next != NULL){
        showLLWithTwoPart(all->next,length);
    }

    return 0;
}