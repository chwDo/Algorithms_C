//
// Created by 蔡昊文 on 29/6/20.
//
#include "GraphWithCC.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "IntQueue.h"

typedef struct GraphRep {
    int **edges;   // adjacency matrix
    int nV;      // #vertices
    int nE;      // #edges
    int nC;
    int *cc;
} GraphRep;

Graph newGraph(int V) {
    assert(V >= 0);
    int i;
    Graph g = malloc(sizeof(GraphRep));
    assert(g != NULL);
    g->nV = V;
    g->nE = 0;
    g->nC = V;
    // allocate memory for each row
    g->edges = malloc(V * sizeof(int *));
    g->cc = malloc(V * sizeof(int));
    assert(g->edges != NULL);
    // allocate memory for each column and initialise with 0
    for (i = 0; i < V; i++) {
        g->cc[i] = i;
        g->edges[i] = calloc(V, sizeof(int));
        assert(g->edges[i] != NULL);
    }

    return g;
}

int numOfVertices(Graph g) {
    return g->nV;
}

// check if vertex is valid in a graph
static bool validV(Graph g, Vertex v) {
    return (g != NULL && v >= 0 && v < g->nV);
}

bool checkConnectedComponent(Graph g, Edge e) {
    return g->cc[e.v] == g->cc[e.w];
}

below is persuade code
//insertEdge(g,(v,w)):
//|  Input graph g, edge (v,w)
//|
//|  if g.edges[v][w]=0 then               // (v,w) not in graph
//|  |  g.edges[v][w]=1, g.edges[w][v]=1   // set to true
//|  |  g.nE=g.nE+1
//           |  |  if g.cc[v]≠g.cc[w] then            // v,w in different components?
//|  |  |  c=min{g.cc[v],g.cc[w]}          // ⇒ merge components c and d
//|  |  |  d=max{g.cc[v],g.cc[w]}
//|  |  |  for all vertices v∈g do
//|  |  |     if g.cc[v]=d then
//|  |  |        g.cc[v]=c                 // move node from component d to c
//|  |  |     else if g.cc[v]=g.nC-1 then
//|  |  |        g.cc[v]=d                 // replace largest component ID by d
//|  |  |     end if
//|  |  |  end for
//|  |  |  g.nC=g.nC-1
//              |  |  end if
//|  end if
//removeEdge(g,(v,w)):
//|  Input graph g, edge (v,w)
//|
//|  if g.edges[v][w]≠0 then               // (v,w) in graph
//|  |  g.edges[v][w]=0, g.edges[w][v]=0   // set to false
//|  |  if not hasPath(g,v,w) then         // v,w no longer connected?
//|  |     dfsNewComponent(g,v,g.nC)       // ⇒ put v + connected vertices into new component
//|  |     g.nC=g.nC+1
//              |  |  end if
//|  end if
//
//dfsNewComponent(g,v,componentID):
//|  Input graph g, vertex v, new componentID for v and connected vertices
//|
//|  g.cc[v]=componentID
//|  for all vertices w adjacent to v do
//|     if g.cc[w]≠componentID then
//|        dfsNewComponent(g,w,componentID)
//|     end if
//|  end if
void unionConnectedComponent(Graph g, Edge e) {
    int targetCC = g->cc[e.v] < g->cc[e.w] ? g->cc[e.v] : g->cc[e.w]; // get smaller one as component index
    int sourceCC = g->cc[e.v] > g->cc[e.w] ? g->cc[e.v] : g->cc[e.w]; // get source index
    int i;
    static int targetIndex = 1;  //record current connect component index
    for (i = 0; i < g->nV; i++) {
        if (targetCC > targetIndex) {
            if (g->cc[i] == sourceCC || g->cc[i] == targetCC) {
                g->cc[i] = targetIndex;
            }
        } else {
            if (g->cc[i] == sourceCC) {
                g->cc[i] = targetCC;
            }
        }

    }
    if (targetCC > targetIndex)
        targetIndex++;
    printf("%d %d %d\n", targetIndex, e.v, e.w);
    g->nC--;
}

void insertEdge(Graph g, Edge e) {
    assert(g != NULL && validV(g, e.v) && validV(g, e.w));
    if (!g->edges[e.v][e.w]) {  // edge e not in graph
        g->edges[e.v][e.w] = 1;
        g->edges[e.w][e.v] = 1;
        g->nE++;
    }
    if (!checkConnectedComponent(g, e)) {
        unionConnectedComponent(g, e);
    }
}

void disunionConnectComponent(Graph g, Edge e) {
    int pointIndex = e.v > e.w ? e.v : e.w;
    int endPointIndex = pointIndex == e.v ? e.w : e.v;
    //bfs the point
    QueueInit();
    bool *markarry = calloc(g->nV, sizeof(bool));
    QueueEnqueue(pointIndex);
    int serachPoint;
    int i;
    while (!QueueIsEmpty()) {
        serachPoint = QueueDequeue();
        for (i = 0; i < g->nV; i++) {
            if(!markarry[i] && g->edges[serachPoint][i]){
                    QueueEnqueue(i);
                    markarry[i] = true;
            }
        }
        if (markarry[endPointIndex]){
            free(markarry);
            return ;   // end loop if find the other way to endpoint
        }
    }
    for (i = 0; i < g->nV; i++){
        if(markarry[i]){
            g->cc[i] = g->nC;
        }
    }
    g->nC++;
    free(markarry);
}

void removeEdge(Graph g, Edge e) {
    assert(g != NULL && validV(g, e.v) && validV(g, e.w));
    if (g->edges[e.v][e.w]) {   // edge e in graph
        g->edges[e.v][e.w] = 0;
        g->edges[e.w][e.v] = 0;
        g->nE--;
    }
    disunionConnectComponent(g, e);
}

bool adjacent(Graph g, Vertex v, Vertex w) {
    assert(g != NULL && validV(g, v) && validV(g, w));

    return (g->edges[v][w] != 0);
}

void showGraph(Graph g) {
    assert(g != NULL);
    int i, j;

    printf("Number of vertices: %d\n", g->nV);
    printf("Number of edges: %d\n", g->nE);
    for (i = 0; i < g->nV; i++)
        for (j = i + 1; j < g->nV; j++)
            if (g->edges[i][j])
                printf("Edge %d - %d\n", i, j);
}

void freeGraph(Graph g) {
    assert(g != NULL);

    int i;
    for (i = 0; i < g->nV; i++)
        free(g->edges[i]);
    free(g->edges);
    free(g);
}

void showcc(Graph g) {
    int i;
    printf("%d\n", g->nC);
    for (i = 0; i < g->nV; i++) {
        printf("%d ", g->cc[i]);
    }
}