#include "PQueue.h"
//#include "Graph.h"
#include <stdio.h>
#include "stdlib.h"

PQueue getPQueue() {
    PQueue res;
    res.head = NULL;
    return res;
}

PQNode* getPQNode(Dot* dot, double priority) {
    PQNode* res = calloc(1, sizeof (PQNode));
    res->dot = dot;
    res->priority = priority;
    return res;
}

int addPQueue(PQueue* this, Dot* dot, double priority) {
    if (this == NULL) return 1;
    PQNode* node = getPQNode(dot, priority);

    if (this->head == NULL) {
        this->head = node;
        return 0;
    }

    PQNode* prev = NULL;
    PQNode* it = NULL;
    for (it = this->head; it != NULL; it = it->next) {
        if (it->priority < node->priority)
            break;
        prev = it;
    }

    if (prev == NULL) {
        PQNode* tmp = this->head;
        this->head = node;
        this->head->next = tmp;
    } else {
        prev->next = node;
        node->next = it;
    }
    return 0;
}

Dot* popPQueue(PQueue* this) {
    if (this == NULL || this->head == NULL) return NULL;

    PQNode* it = this->head;
    PQNode* prev = NULL;
    for (; it->next != NULL; it = it->next) {
        prev = it;
    }

    if (prev == NULL) {
        PQNode* tmp = this->head;
        this->head = NULL;
        Dot* res = tmp->dot;
        free(tmp);
        return res;
    } else {
        PQNode* tmp = it;
        prev->next = NULL;
        Dot* res = it->dot;
        free(tmp);
        return res;
    }
}


int isEmpty(PQueue* this) {
    return this->head == NULL;
}