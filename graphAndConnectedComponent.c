//
// Created by 蔡昊文 on 29/6/20.
//

#include <stdio.h>
#include "Graph.h"
#include <stdlib.h>
#include <string.h>
int compare(const void* a, const void* b){
    return ( *(int*)b - *(int*)a );
}


void showInformationAboutDegree(Graph g) {
    int V = numOfVertices(g);
    int *degreeVector = calloc(V, sizeof(int));
    bool *minDegreeNodes = calloc(V,sizeof(bool));
    bool *maxDegreeNodes = calloc(V,sizeof(bool));
    int i, j;
    int maxDegree = 0,minDegree = V;
    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            if(adjacent(g,i,j)){
                degreeVector[i]++;
            }
        }
        if(degreeVector[i] >= maxDegree){
            if(degreeVector[i] == maxDegree)
                maxDegreeNodes[i] = true;
            else{
                maxDegree = degreeVector[i];
                memset(maxDegreeNodes,false,V * sizeof(bool));
                maxDegreeNodes[i] = true;
            }
        }
        if(degreeVector[i] <= minDegree){
            if(degreeVector[i] == minDegree)
                minDegreeNodes[i] = true;
            else{
                minDegree = degreeVector[i];
                memset(minDegreeNodes,false,V * sizeof(bool));
                minDegreeNodes[i] = true;
            }
        }
    }
    printf("Minimum degree: %d\n",minDegree);
    printf("Maximum degree: %d\n",maxDegree);
    printf("Nodes of minimum degree:\n");
    for(i=0;i<V;i++){
        if(minDegreeNodes[i])
            printf("%d\n",i);
    }
    free(minDegreeNodes);
    printf("Nodes of maximum degree:\n");
    for(i=0;i<V;i++){
        if(maxDegreeNodes[i])
            printf("%d\n",i);
    }
    free(maxDegreeNodes);
    qsort(degreeVector,V, sizeof(int),compare);
}

//int main() {
//    int V, v, w;
//    printf("Enter the number of vertices:");
//    scanf("%d", &V);
//    Graph g = newGraph(V);
//    Edge e;
//
//    while (1) {
//        printf("Enter an edge (from):");
//        if (!scanf("%d", &v))
//            break;
//        printf("Enter an edge (to):");
//        if (!scanf("%d", &w))
//            break;
//        e.v = v;
//        e.w = w;
//        insertEdge(g, e);
//    }
//    showInformationAboutDegree(g);
//    printf("Done.\n");
//    return 0;
//}