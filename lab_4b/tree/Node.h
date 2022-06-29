#ifndef LAB4A_NODE_H
#define LAB4A_NODE_H

typedef struct Node {
    char* key;
    char* data;
    int version;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
    int balance;
} Node;


Node* getNode(char* key, char* data);

#endif
