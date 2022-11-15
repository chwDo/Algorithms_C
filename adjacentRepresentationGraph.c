//
// Created by 蔡昊文 on 3/7/20.
//

#include "adjacentRepresentationGraph.h"
#include "assert.h"
#include <stdlib.h>
#include <stdio.h>
#include "List.h"
typedef struct adjacentRepresentationGraphRep{
    List *edges;
    int nE;
    int nV;
}adjacentRepresentationGraphRep;


AdjGraph newAdjGraph(int V){
    assert(V >= 0);
    int i;

    AdjGraph g= malloc(sizeof(adjacentRepresentationGraphRep));
    assert(g!=NULL);
    g->nV = V;
    g->nE = 0;

    g->edges = malloc(V * sizeof(List));
    assert(g->edges != NULL);

    for(i=0;i<V;i++)
        g->edges[i] = NULL;

    return g;

}

int   adjNumOfVertices(AdjGraph g){
    return g->nV;
}
bool adjValidV(AdjGraph g,Vertex v){
    return (g != NULL && v >= 0 && v < g->nV);
}
void  adjInsertEdge(AdjGraph g, Edge e){
    assert(adjValidV(g,e.v));

    g->edges[e.v] = insertLL(g->edges[e.v],e.w);
   // g->edges[e.w] = insertLL(g->edges[e.w],e.v);
    g->nE++;
}
void  adjRemoveEdge(AdjGraph g, Edge e){
    assert(g != NULL && adjValidV(g,e.v));

    if(inLL(g->edges[e.v],e.w)){
        deleteLL(g->edges[e.v],e.w);
        g->nE --;
    }
}
bool  adjAdjacent(AdjGraph g, Vertex v, Vertex w){
    assert(g != NULL && adjValidV(g,v));

    return inLL(g->edges[v], w);
}
void  adjShowGraph(AdjGraph g){
    assert(g != NULL);
    int i;

    printf("Number of vertices: %d\n", g->nV);
    printf("Number of edges: %d\n", g->nE);
    for(i = 0;i<g->nV;i++){
        printf("%d - ",i);
        showLL(g->edges[i]);
    }
}
void  adjFreeGraph(AdjGraph g){
    assert(g != NULL);
    int i;

    for(i =0;i<g->nV;i++){
        free(g->edges[i]);
    }
    free(g->edges);
    free(g);
}