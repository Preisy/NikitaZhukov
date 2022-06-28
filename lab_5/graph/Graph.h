#ifndef LAB_5_GRAPH_H
#define LAB_5_GRAPH_H

#include "stdlib.h"

typedef struct Dot {
    struct Dot* next;
    int x;
    int y;
    double r;
} Dot;

Dot* getDot(int x, int y);

typedef struct Node {
    struct Node* next;
    Dot* dot;
    Dot* dotHead;
} Node;

typedef struct Graph {
    Node* nodeHead;
} Graph;

Graph getGraph();

int addVertexGraph(Graph* this, int x, int y);

int addEdgeGraph(Graph* this, int x1, int y1, int x2, int y2);

int deleteVertexGraph(Graph* this, int x, int y);

int deleteEdgeGraph(Graph* this, int x1, int y1, int x2, int y2);

int findGraph(Graph* this, int x1, int y1, int x2, int y2);

int sFindGraph(Graph* this, int x1, int y1, int x2, int y2);

void printGraph(Graph* this);

void graphDestructor(Graph* this);

#endif //LAB_5_GRAPH_H
