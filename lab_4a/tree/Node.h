#ifndef LAB4A_NODE_H
#define LAB4A_NODE_H

typedef struct Node {
    int key;
    const char *data;
    int version;
    struct Node *parent;
    struct Node *left;
    struct Node *right;
} Node;


Node *getNode(int key, char *data);

#endif
