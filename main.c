#include <stdio.h>
#include "IntQueue.h"
int main(){
    int i,n;
    scanf("%d",&n);
    int number;
    for (i = 0; i < n; i++) {
        scanf("%d",&number);
        QueueEnqueue(number);
    }
    while(!QueueIsEmpty()) {
        printf("%d\n",QueueDequeue());
    }
    return 0;
}