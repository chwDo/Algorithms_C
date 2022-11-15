//
// Created by 蔡昊文 on 3/7/20.
//

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "WGraph.h"

typedef struct PopularityVector {
    int inDegree;
    int outDegree;
    float popularity;
} PVectorRep;

int cmp(const void* a, const void* b) {
    PVectorRep *p =(PVectorRep *)a;
    PVectorRep *q =(PVectorRep *)b;
   // if(p->popularity > q->popularity) return -1;
    return q->popularity > p->popularity;
}
int main() {
    int V, v, w;
    printf("Enter the number of vertices: ");
    scanf("%d", &V);
    Edge e;
    PVectorRep *pv = calloc(V, sizeof(PVectorRep));
    while (1) {
        printf("Enter an edge (from): ");
        if (!scanf("%d", &v))
            break;
        printf("Enter an edge (to): ");
        if (!scanf("%d", &w))
            break;
        e.v = v;
        e.w = w;
        pv[e.v].outDegree++;
        pv[e.w].inDegree++;
    }
    printf("Done.\n\n");
    int i;
    for (i = 0; i < V; i++) {
        if (pv[i].outDegree == 0)
            pv[i].outDegree = 0.5;
        pv[i].popularity = pv[i].inDegree / pv[i].outDegree;
        pv[i].inDegree = i; //record index in inDegree memory
    }
    qsort(pv, V, sizeof(pv[0]), cmp);
    printf("Popularity ranking:\n");
    for (i = 0; i < V; i++) {
        printf("%d %.1f\n", pv[i].inDegree, pv[i].popularity);
    }
    free(pv);
}
