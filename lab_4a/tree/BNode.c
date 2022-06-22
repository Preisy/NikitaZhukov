#include <stdlib.h>
#include "BNode.h"

BNode *getBNode(unsigned key, const char *data) {
    BNode *node = calloc(1, sizeof(BNode));
    node->key = key;
    node->data = data;
    return node;
}
