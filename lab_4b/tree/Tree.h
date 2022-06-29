#ifndef LAB4A_TREE_H
#define LAB4A_TREE_H

#include "Node.h"

typedef enum DrawMode {
    Default,
    Parent,
} DrawMode;

typedef struct Tree {
    Node* root;
} Tree;

Tree* getTree();

Tree* getTreeFromFile(char* fileName);

int addTree(Tree* tree, char* key, char* data);

int deleteTree(Tree* this, char* key);

int printTree(Tree* tree);

int writeTree(Tree* tree, DrawMode mode);

int findTree(Tree* tree, char* key, Node*** res, int* len);

int sFindTree(Tree* tree, Node*** res, int* len);

int traversalTree(Tree* tree, char* min, char* max);

void treeDestructor(Tree* tree);

#endif
