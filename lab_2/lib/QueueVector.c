#include "Queue.h"
#include "stdio.h"
#include "string.h"

struct Queue {
    Pair* arr;
    int bufLength;
    int head;
    int tail;
    int length;
};

Queue* getQueue() {
    Queue* res = (Queue*) malloc(sizeof (Queue));
    int bufLength = 10;
    res->arr = (Pair*) malloc(sizeof (Pair) * bufLength);
    res->bufLength = bufLength;
    res->head = res->tail = -1;
    res->length = 0;
    return res;
}

int getSizeQueue() {
    return sizeof (Queue);
}

void deleteQueue(Queue* this) {
    free(this->arr);
    free(this);
}

int pushQueue(Queue* this, Pair data) {
    if (this == NULL || this->length == this->bufLength) return 0;

    ++this->length;
    if (this->tail == -1 && this->head == -1) {
        this->tail = this->head = 0;
        this->arr[this->tail] = data;
        return 1;
    }

    this->tail = (this->tail + 1) % this->bufLength;
    this->arr[this->tail] = data;
    return 1;
}

int isEmptyQueue(Queue* this) {
    return this->length == 0;
}

Pair popQueue(Queue* this) {
    if (isEmptyQueue(this)) {
        return getPair("", -1);
    }

    Pair data = this->arr[this->head];
    if (this->head == this->tail) {
        this->head = this->tail = -1;
    } else {
        this->head = (this->head + 1) % this->bufLength;
    }
    --this->length;
    return data;
}

Pair* topQueue(Queue* this) {
    if (isEmptyQueue(this)) {
        return NULL;
    }

    return &this->arr[this->head];
}

char* toStringQueue(Queue* this) {
    int bufLength = 10;
    char* res = (char*) malloc (sizeof (char) * (bufLength + 1));
    res[0] = '\0';
    int i = this->head;
    for (int count = 0; count < this->length; ++count) {
        char* str = this->arr[i].id;
        if (bufLength < strlen(res) + strlen(this->arr[i].id) + 1) {
            bufLength *= 2;
            res = (char*) realloc(res, sizeof (char) *(bufLength + 1));
        }
        strcat(res, str);
        strcat(res, " ");
        i = (i + 1) % this->bufLength;
    }
    int n = strlen(res);
    char* buf = (char*) calloc(n + 1, sizeof (char));
//    res = (char*) realloc(res, sizeof (char) * (n + 1));
    memcpy(buf, res, sizeof (char) * n);
    buf[n] = '\0';
    free(res);
    return buf;
}
