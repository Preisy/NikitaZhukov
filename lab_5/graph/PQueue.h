#ifndef LAB_5_PQUEUE_H
#define LAB_5_PQUEUE_H

#include "Graph.h"

typedef struct PQNode {
    Dot* dot;
    double priority;
    struct PQNode* next;
} PQNode;

typedef struct PQueue {
    PQNode* head;
} PQueue;

PQueue getPQueue();

int addPQueue(PQueue* this, Dot* dot, double priority);

Dot* popPQueue(PQueue* this);

int isEmpty(PQueue* this);

#endif //LAB_5_PQUEUE_H
