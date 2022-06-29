#include "stdlib.h"
#include "Node.h"

Node* getNode(char* key, char* data) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->key = key;
    node->data = data;
    node->version = 0;
    node->balance = 0;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;

    return node;
}
