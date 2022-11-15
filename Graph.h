//
// Created by 蔡昊文 on 29/6/20.
//

#ifndef INC_9024_C_PROJECT_GRAPH_H
#define INC_9024_C_PROJECT_GRAPH_H

#endif //INC_9024_C_PROJECT_GRAPH_H
#include <stdbool.h>
typedef struct GraphRep *Graph;

// vertices are ints
typedef int Vertex;

// edges are pairs of vertices (end-points)
typedef struct Edge {
    Vertex v;
    Vertex w;
} Edge;

Graph newGraph(int);
int   numOfVertices(Graph);
void  insertEdge(Graph, Edge);
void  removeEdge(Graph, Edge);
bool  adjacent(Graph, Vertex, Vertex);
void  showGraph(Graph);
void  freeGraph(Graph);