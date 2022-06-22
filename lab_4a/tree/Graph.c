#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

void _recWrite(FILE *file, Node *node, int *leaves, DrawMode mode) {
    if (node == NULL) return;
    if (node->left == NULL) {
        fprintf(file, "\"%d: %s (%d)\"->null%d[style=invis];", node->key, node->data, node->version, *leaves);
        (*leaves)++;
    } else {
        fprintf(file, "\"%d: %s (%d)\"->\"%d: %s (%d)\";", node->key, node->data, node->version,
                node->left->key, node->left->data, node->left->version);
        if (mode == Parent)
            fprintf(file, "\"%d: %s (%d)\"->\"%d: %s (%d)\";", node->left->key, node->left->data, node->left->version,
                    node->left->parent->key, node->left->parent->data, node->left->parent->version);

    }
    if (node->right == NULL) {
        fprintf(file, "\"%d: %s (%d)\"->null%d[style=invis];", node->key, node->data, node->version, *leaves);
        (*leaves)++;
    } else {
        fprintf(file, "\"%d: %s (%d)\"->\"%d: %s (%d)\";", node->key, node->data, node->version,
                node->right->key, node->right->data, node->right->version);
        if (mode == Parent)
            fprintf(file, "\"%d: %s (%d)\"->\"%d: %s (%d)\";", node->right->key, node->right->data, node->right->version,
                    node->right->parent->key, node->right->parent->data, node->right->parent->version);

    }
    _recWrite(file, node->left, leaves, mode);
    _recWrite(file, node->right, leaves, mode);
}

int createGraph(Tree *tree, DrawMode mode) {
    if (tree == NULL || tree->root == NULL)
        return 1;

//    FILE *file = fopen("output/tree.dot", "w"); for makefile
//    FILE *file = fopen("../output/tree.dot", "w");
    FILE *file = fopen("/mnt/d/C/2sem_aisd/NikitaZukov/lab_4a/output/tree.dot", "w"); // todo поменять
    if (file == NULL) return 1;

    fprintf(file, "digraph binaryTree {\nnode[shape=circle,color=black,fontcolor=black,fontsize=10];");
    int count = 0;

    fprintf(file, "\"%d: %s (%d)\"", tree->root->key, tree->root->data, tree->root->version);
    _recWrite(file, tree->root, &count, mode);
    for (int i = 0; i < count; ++i) {
        fprintf(file, "null%d[style=invis];", i);
    }


    fprintf(file, "}");
    fclose(file);

//    system("dot -Tpng -O output/tree.dot"); for makefile
//    system("dot -Tpng -O ../output/tree.dot");
    system("dot -Tpng -O /mnt/d/C/2sem_aisd/NikitaZukov/lab_4a/output/tree.dot"); // todo поменять
    return 0;
}
