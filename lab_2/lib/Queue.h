#ifndef LAB_2_QUEUE_H
#define LAB_2_QUEUE_H

#include "pair.h"
#include "stdlib.h"

typedef struct Queue Queue;

Queue* getQueue();

//int getSizeQueue();

void deleteQueue(Queue* this);

int pushQueue(Queue* this, Pair data);

int isEmptyQueue(Queue* this);

Pair popQueue(Queue* this);

Pair* topQueue(Queue* this);

char* toStringQueue(Queue* this);

#endif //LAB_2_QUEUE_H
