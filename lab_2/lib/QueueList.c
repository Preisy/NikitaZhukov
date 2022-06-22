#include "Queue.h"
#include "string.h"

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

char* toStringQueue(Queue* this) {
    int bufLength = 10;
    char* res = (char*) malloc (sizeof (char) * (bufLength + 1));
    res[0] = '\0';

    for (Node* it = this->head; it != NULL; it = it->next) {
        char* str = it->data.id;
        if (bufLength < strlen(res) + strlen(it->data.id) + 1) {
            bufLength *= 2;
            res = (char*) realloc(res, sizeof (char) *(bufLength + 1));
        }
        strcat(res, str);
        strcat(res, " ");
    }

//    int i = this->head;
//    for (int count = 0; count < this->length; ++count) {
//        char* str = this->arr[i].id;
//        if (bufLength < strlen(res) + strlen(this->arr[i].id) + 1) {
//            bufLength *= 2;
//            res = (char*) realloc(res, sizeof (char) *(bufLength + 1));
//        }
//        strcat(res, str);
//        strcat(res, " ");
//        i = (i + 1) % this->bufLength;
//    }


    int n = strlen(res);
    char* buf = (char*) calloc(n + 1, sizeof (char));
    memcpy(buf, res, sizeof (char) * n);
    buf[n] = '\0';
    free(res);
    return buf;
}

