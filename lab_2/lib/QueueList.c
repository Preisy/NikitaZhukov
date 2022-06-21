#include "Queue.h"

typedef struct Node {
    struct Node *next;
    Pair data;
} Node;

struct Queue {
    Node *head;
    Node *tail;
};

Node* getNode(Pair data) {
    Node* res = (Node*) malloc(sizeof(Node));
    res->next = NULL;
    res->data = data;
    return res;
}

void deleteNode(Node* this) {
    free(this);
}

Queue* getQueue() {
    Queue* res = (Queue*) malloc(sizeof(Queue));
    res->head = res->tail = NULL;
    return res;
}

int getSizeQueue() {
    return sizeof (Queue);
}

void deleteQueue(Queue* this) {
    Node *it = this->head;
    while (it != NULL) {
        Node *tmp = it;
        it = it->next;
        free(tmp);
    }
    free(this);
}

int pushQueue(Queue* this, Pair data) {
    Node* tmp = getNode(data);
    if (this->head == NULL) {
        this->head = this->tail = tmp;
    } else {
        this->tail->next = tmp;
        this->tail = tmp;
    }
    return 1;
}

int isEmptyQueue(Queue* this) { return this->head == NULL; }

Pair popQueue(Queue* this) {
    if (isEmptyQueue(this)) {
        return getPair("", -1);
    }
    Node *tmp = this->head;
    Pair data = tmp->data;
    this->head = this->head->next;
    deleteNode(tmp);
    return data;
}

Pair* topQueue(Queue* this) {
    if (isEmptyQueue(this)) {
        return NULL;
    }
    return &this->head->data;
}

