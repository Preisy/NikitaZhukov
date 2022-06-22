#ifndef LAB4A_TREE_H
#define LAB4A_TREE_H

#include "Node.h"

enum DrawMode;

typedef struct Tree {
    Node *root;
} Tree;

Tree *getTree();

Tree *getTreeFromFile(char *fileName);

int addTree(Tree *tree, int key, char *data);

int deleteTree(Tree *tree, int key);

int printTree(Tree *tree);

int writeTree(Tree *tree, enum DrawMode mode);

int findTree(Tree *tree, int key, Node ***res, int *len);

int findMinTree(Tree *tree, Node ***res, int *len);

int traversalTree(Tree *tree);

void treeDestructor(Tree *tree);

void treeDestructorDeep(Tree *tree);

#endif
