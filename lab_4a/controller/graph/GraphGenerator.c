#include <stdio.h>
#include <stdlib.h>
#include "GraphGenerator.h"

#define DOT_HEADER "digraph binaryTree {\nnode[shape=circle,color=black,fontcolor=black,fontsize=10];\n"
#define DOT_FOOTER "}"
#define DOT_EMPTY_LEAVE " \"%d: %s (%d)\" -> null%d[style=invis];\n"
#define DOT_EMPTY " null%d[style=invis];\n"
#define DOT_LEAVE " \"%d: %s (%d)\" -> \"%d: %s (%d)\";\n"

void _writeDotNLR(FILE *file, const BNode *node, int *leaves, DrawMode mode) {
    if (node == NULL) return;
    if (node->left == NULL) {
        fprintf(file, DOT_EMPTY_LEAVE, node->key, node->data, node->generation, *leaves);
        (*leaves)++;
    } else {
        fprintf(file, DOT_LEAVE, node->key, node->data, node->generation,
                node->left->key, node->left->data, node->left->generation);
        if (mode == PARENT)
            fprintf(file, DOT_LEAVE, node->left->key, node->left->data, node->left->generation,
                    node->left->parent->key, node->left->parent->data, node->left->parent->generation);

    }
    if (node->right == NULL) {
        fprintf(file, DOT_EMPTY_LEAVE, node->key, node->data, node->generation, *leaves);
        (*leaves)++;
    } else {
        fprintf(file, DOT_LEAVE, node->key, node->data, node->generation,
                node->right->key, node->right->data, node->right->generation);
        if (mode == PARENT)
            fprintf(file, DOT_LEAVE, node->right->key, node->right->data, node->right->generation,
                    node->right->parent->key, node->right->parent->data, node->right->parent->generation);

    }
    _writeDotNLR(file, node->left, leaves, mode);
    _writeDotNLR(file, node->right, leaves, mode);
}

int createPngGraph(const BinaryTree *tree, DrawMode mode) {
    if (tree == NULL || tree->root == NULL) return 1;
//    FILE *file = fopen("output/binary_tree.dot", "w"); for makefile
//    FILE *file = fopen("../output/binary_tree.dot", "w");
    FILE *file = fopen("/mnt/d/C/2sem_aisd/NikitaZukov/lab_4a/output/binary_tree.dot", "w");
    if (file == NULL) return 1;

    fprintf(file, DOT_HEADER);
    int leaves = 0;

    fprintf(file, "\"%d: %s (%d)\"\n", tree->root->key, tree->root->data, tree->root->generation);
    _writeDotNLR(file, tree->root, &leaves, mode);
    for (int i = 0; i < leaves; ++i) {
        fprintf(file, DOT_EMPTY, i);
    }
    fprintf(file, DOT_FOOTER);
    fclose(file);
//    system("dot -Tpng -O output/binary_tree.dot"); for makefile
//    system("dot -Tpng -O ../output/binary_tree.dot");
    system("dot -Tpng -O /mnt/d/C/2sem_aisd/NikitaZukov/lab_4a/output/binary_tree.dot");
    return 0;
}
