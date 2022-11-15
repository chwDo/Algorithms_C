#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "list.h"

#define LENGTH 32  //Names require no more than 31 characters and will not use any spaces.

typedef struct {
    int time;// 4 digits from 0000 to 2359
    int indexOfStop;
} scheduleRep;

typedef struct indexNode {  // struct aiming to find the corresponding index of word
    int index;
    char name[LENGTH];
} indexNodeRep;

typedef struct {  //
    int time;
    int indexOfBus;
    int ordinal;
    bool visited;
} stopNodeWithMark;

typedef struct {
    int time;// 4 digits from 0000 to 2359
    int indexOfBus;
    int indexOfStop;
    int ordinal;
} answerNode;

int numberOfStops, numberOfSchedules;; //this value store number of stops and schedules
char **stops;  //No stop name will be input more than once.
scheduleRep **schedules;    //store schedules
indexNodeRep *stopIndex[26]; // establish index for quick accessing stop
stopNodeWithMark **via; // store the map
int timeThreshold[2];  // timeThreshold[0] =  latest timeThreshold arrive destination  timeThreshold[1] = earliest timeThreshold arrive destination
int findIndex(char stopName[32]);

List answer[2];
int flag = false;

void stopsInit() {  //init stops
    printf("Enter the total number of stops on the network: ");
    scanf("%d", &numberOfStops); // NOLINT(cert-err34-c)
    int i;
    stops = malloc(numberOfStops * sizeof(char *));
    for (i = 0; i < 26; i++) {
        stopIndex[i] = calloc(numberOfStops + 1, sizeof(indexNodeRep));
    }

    for (i = 0; i < numberOfStops; i++) {
        stops[i] = malloc(LENGTH * sizeof(char));
        scanf("%s", stops[i]);
        int index = (stops[i][0] - 'A') % 26;
        stopIndex[index][0].index++;    //position 0 store the number of elements in start with same letter
        stopIndex[index][stopIndex[index][0].index].index = i;
        strcpy(stopIndex[index][stopIndex[index][0].index].name, stops[i]);
    }
}

void scheduleInit() { //init buses route and via vector
    assert(numberOfSchedules >= 0);
    printf("Enter the number of schedules: ");
    scanf("%d", &numberOfSchedules);
    int i, j;
    schedules = malloc(numberOfSchedules * sizeof(scheduleRep *));
    int time, n;
    char name[LENGTH];

    via = malloc(numberOfStops * sizeof(stopNodeWithMark *));
    for (i = 0; i < numberOfStops; i++) {
        via[i] = calloc((numberOfSchedules + 1), sizeof(stopNodeWithMark));
    }
    int index;

    for (i = 0; i < numberOfSchedules; i++) {
        printf("Enter the number of stops: ");
        scanf("%d", &n);
        assert(n >= 0);
        schedules[i] = malloc((n + 1) * sizeof(scheduleRep));
        assert(schedules[i] != NULL);
        schedules[i][0].time = n;  //store length of schedule at index 0 with 1 offset
        j = 1;
        while (n--) {
            scanf("%d", &time);
            scanf("%s", name);

            index = findIndex(name);
            via[index][++via[index][0].time].indexOfBus = i;  //initialize via array
            via[index][via[index][0].time].time = time;
            via[index][via[index][0].time].visited = false;
            via[index][via[index][0].time].ordinal = j; //22

            schedules[i][j].time = time;
            schedules[i][j].indexOfStop = index;
            j++;
        }
    }
}

int findIndex(char stopName[32]) {
    int i;
    int indexOfLetter = (stopName[0] - 'A') % 26;
    assert(indexOfLetter >= 0); // first letter must be capitalized
    for (i = 0; i <= stopIndex[indexOfLetter][0].index; i++) {
        if (!strcmp(stopIndex[indexOfLetter][i].name, stopName))  //find the index of stop store in stops
            return stopIndex[indexOfLetter][i].index;
    }
    return -1;
}

answerNode fineTheNextStop(int currentStop, int currentTime) {
    answerNode nextStop;
    int i, mark = -1;
    nextStop.time = -1;
    nextStop.indexOfStop = -1;
    nextStop.indexOfBus = -1;

    for (i = 1; i <= via[currentStop][0].time; i++) {
        if (!via[currentStop][i].visited && via[currentStop][i].time >= currentTime &&
            via[currentStop][i].time >= nextStop.time) {
            nextStop.indexOfStop = currentStop;
            nextStop.time = via[currentStop][i].time;
            nextStop.indexOfBus = via[currentStop][i].indexOfBus;
            nextStop.ordinal = via[currentStop][i].ordinal;
            mark = i;
        }
    }

    if (mark != -1) {
        answer[0] = insertLL(answer[0], nextStop.indexOfBus,nextStop.ordinal, nextStop.time,
                             stops[nextStop.indexOfStop]);
        via[currentStop][mark].visited = true;
        if(nextStop.ordinal <schedules[nextStop.indexOfBus][0].time){  //exist nextstop
            nextStop.indexOfStop = schedules[nextStop.indexOfBus][nextStop.ordinal + 1].indexOfStop;
            nextStop.time = schedules[nextStop.indexOfBus][nextStop.ordinal + 1].time;
            nextStop.ordinal++;
        }
    }
    return nextStop; // if cannot find the next stop from current stop

}

List regularization(List L) {   //add the change station into List
    answerNode currentStop;
    List temp, head = L;
    while (!valid(getTheNextNode(L))) {
        temp = getTheNextNode(L);
        if (getIndexOfBus(L) != getIndexOfBus(temp)) {  //sure access right memory
            currentStop.indexOfBus = getIndexOfBus(temp);
            currentStop.ordinal = getOrdinal(temp);
            temp = insertLL(temp,currentStop.indexOfBus,currentStop.ordinal+1,
                    schedules[currentStop.indexOfBus][currentStop.ordinal+1].time,
                            stops[schedules[currentStop.indexOfBus][currentStop.ordinal+1].indexOfStop]);
            setNextNode(L,temp);
        }
        L = temp;
    }
    return head;
}

void query(int source, int destination, int departTime) {
    answerNode nextStop;
    while ((nextStop = fineTheNextStop(source, departTime)).indexOfStop != -1) {
        if (destination == nextStop.indexOfStop && nextStop.time == timeThreshold[1]) {
            answer[0] = insertLL(answer[0], nextStop.indexOfBus,nextStop.ordinal, nextStop.time,
                                 stops[nextStop.indexOfStop]);
            answer[0] = regularization(answer[0]);
            printf("\n");
            showLL(answer[0]);
            flag = true;
            return;   //because DFS prioritized latest departing bus,so if time == earliest time that mean find the best path
        }
        if (nextStop.time <= timeThreshold[0]) {  // End search processing if time > the latest time can arrive destination
            if (destination == nextStop.indexOfStop) {  // if arrive dest
                timeThreshold[0] = nextStop.time;
                if (answer[1] == NULL ||
                    answer[1] >= answer[0]) { // if the recorded route is not better than current one
                    freeLL(answer[1]);
                    answer[1] = newList();
                    answer[1] = copyLL(answer[0], answer[1]);
                    answer[1] = insertLL(answer[1], nextStop.indexOfBus,nextStop.ordinal, nextStop.time,
                                         stops[nextStop.indexOfStop]);
                }
            } else {
                query(nextStop.indexOfStop, destination, nextStop.time);
            }
        }
        answer[0] = deleteLLAElementFromHead(
                answer[0]);  // cannot find valid route at this stop, delete from answer route
    }
}

void reset() {
    freeLL(answer[0]);
    freeLL(answer[1]);
    int i, j;
    for (i = 0; i < numberOfStops; i++) {
        for (j = 1; j <= via[i][0].time; j++) {
            via[i][j].visited = false;
        }
    }
    flag = false;
}

void searchInit(int destination, int departTime) {
    timeThreshold[0] = 0;
    timeThreshold[1] = 2360;
    int i;
    for (i = 1; i <= via[destination][0].time; i++) {
        if (via[destination][i].time >= departTime) {
            timeThreshold[0] = timeThreshold[0] > via[destination][i].time ? timeThreshold[0] : via[destination][i].time;
            timeThreshold[1] = timeThreshold[1] < via[destination][i].time ? timeThreshold[1] : via[destination][i].time;
        }
    }
    answer[0] = newList();
    answer[1] = newList();
}
void freeAll(){
    int i;
    for(i = 0; i<numberOfStops;i++ ){
        free(stops[i]);
        free(via[i]);
    }
    for(i = 0;i<26;i++){
        free(stopIndex[i]);
    }
    for (i = 0; i < numberOfSchedules; i++) {
        free(schedules[i]);
    }
    free(schedules);
    free(stops);
    free(via);
}
int main() {
    stopsInit();
    scheduleInit();
    char S[32], D[32];
    int source, destination, departTime;
    printf("\nFrom: ");
    scanf("%s", S);   // in case first input is done
    while (strcmp(S, "done") != 0) {
        printf("To: ");
        scanf("%s", D);
        printf("Depart at: ");
        scanf("%d", &departTime);
        destination = findIndex(D);
        source = findIndex(S);
        searchInit(destination, departTime);
        query(source, destination, departTime);
        if (!flag) {   //if did not find the earliest path or no path
            if (answer[1] != NULL) {
                answer[1] = regularization(answer[1]);
                printf("\n");
                showLL(answer[1]);
                flag = true;
            } else {
                printf("\nNo connection found.\n");
            }
        }
        reset();
        printf("\nFrom: ");
        scanf("%s", S);
    }
    printf("Thank you for using goNSW.\n");
    freeAll();
    return 0;
}
/*Complexity Analysis

My program is actually a DFS search using via array, Hence the worst-case might search every node in via array.
For one query processing, need to initialize stops array(O(n)) schedules array(O(m)) and via array(m * k(assuming number k of stops on a single train is same)).
In addition to the cost of initialization, the worst-case might search through whole via array (m * k(assume v)).
In summary, the total cost is O(n+m+2*m*K) = O(n+m*k).

 */