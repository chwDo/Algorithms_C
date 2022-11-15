// Starting code for Dijkstra's algorithm ... COMP9024 20T2

#include <stdio.h>
#include <stdbool.h>
#include "PQueue.h"

#define VERY_HIGH_VALUE 999999
bool setIsEmpty(const bool vSet[],int nV){
    int i;
    for(i=0;i<nV;i++){
        if(vSet[i])
            return false; //if any v has not been processed
    }
    return true;
}
int minDist(const bool vSet[],const int dist[],int nV){
    int indexOfMinDist = 0,minDist = VERY_HIGH_VALUE;
    int i;
    for(i=0;i<nV;i++){
       if(vSet[i] && dist[i]<=minDist){
           minDist = dist[i];
           indexOfMinDist = i;
       }
    }
    return indexOfMinDist;
}
void dijkstraSSSP(Graph g, Vertex source) {
    int  dist[MAX_NODES];
    int  pred[MAX_NODES];
    bool vSet[MAX_NODES];  // vSet[v] = true <=> v has not been processed
    int s;

    int nV = numOfVertices(g);
    for (s = 0; s < nV; s++) {
        dist[s] = VERY_HIGH_VALUE;
        pred[s] = -1;
        vSet[s] = true;
    }
    dist[source] = 0;
    pred[source] = source;
    int index,weight;
    int i;
    while(!setIsEmpty(vSet,nV)){
        index = minDist(vSet,dist,nV);
        for(i=0;i<nV;i++){   //relaxation
            weight = adjacent(g, index, i);
            if(weight){
                if(dist[index] + weight < dist[i]){
                    dist[i] = dist[index] + weight;
                    pred[i] = index;
                }
            }
        }
        vSet[index] = false;
    }
    int length=0;
    int path[MAX_NODES];
    Vertex preindex;
    for(i=0;i<nV;i++){
        printf("%d: ",i);
        if(dist[i]==VERY_HIGH_VALUE)
            printf("no path\n");
        else{
            printf("distance = %d, shortest path: ",dist[i]);
            if(i == source){
                printf("%d\n",source); // no way from source to source
            } else{
                preindex = pred[i];
                length=0;
                path[0] = i;  // the first node must be target node
                while(source != preindex){
                    length++;
                    path[length] = preindex;
                    preindex = pred[preindex];
                }
                printf("%d",source);
                int j;
                for(j = length;j>=0;j--){
                        printf("-");
                        printf("%d",path[j]);
                }
                printf("\n");
            }
        }
    }
}

void reverseEdge(Edge *e) {
    Vertex temp = e->v;
    e->v = e->w;
    e->w = temp;
}

int main(void) {
    Edge e;
    int  n, source;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    Graph g = newGraph(n);

    printf("Enter the source node: ");
    scanf("%d", &source);
    printf("Enter an edge (from): ");
    while (scanf("%d", &e.v) == 1) {
        printf("Enter an edge (to): ");
        scanf("%d", &e.w);
        printf("Enter the weight: ");
        scanf("%d", &e.weight);
        insertEdge(g, e);
        reverseEdge(&e);               // ensure to add edge in both directions
        insertEdge(g, e);
        printf("Enter an edge (from): ");
    }
    printf("Done.\n");

    dijkstraSSSP(g, source);
    freeGraph(g);
    return 0;
}