//
// Created by 蔡昊文 on 3/7/20.
//

#ifndef INC_9024_C_PROJECT_ADJACENTREPRESENTATIONGRAPH_H
#define INC_9024_C_PROJECT_ADJACENTREPRESENTATIONGRAPH_H

#endif //INC_9024_C_PROJECT_ADJACENTREPRESENTATIONGRAPH_H
#include <stdbool.h>
typedef struct adjacentRepresentationGraphRep *AdjGraph;

typedef int Vertex;

// edges are pairs of vertices (end-points)
typedef struct Edge {
    Vertex v;
    Vertex w;
} Edge;

AdjGraph newAdjGraph(int V);
int   adjNumOfVertices(AdjGraph);
void  adjInsertEdge(AdjGraph, Edge);
void  adjRemoveEdge(AdjGraph, Edge);
bool  adjAdjacent(AdjGraph, Vertex, Vertex);
void  adjShowGraph(AdjGraph);
void  adjFreeGraph(AdjGraph);