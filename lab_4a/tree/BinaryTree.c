#define  _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include "BinaryTree.h"
#include "GraphGenerator.h"

BinaryTree *getBinaryTree() {
    return calloc(1, sizeof(BinaryTree));
}

BinaryTree *getBinaryTreeFromFile(const char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) return NULL;
    BinaryTree *tree = getBinaryTree();
    char *line = NULL;
    while (!feof(file)) {
        unsigned key;
        size_t len;
        if (fscanf(file, "%d\n", &key) <= 0) break;
        if (getline(&line, &len, file) <= 0) break;
        char *data = malloc(len + 1);
        strcpy(data, line);
        addBT(tree, key, data);
    }
    free(line);
    fclose(file);
    return tree;
}


void _destroyBNode(BNode *node) {
    if (node == NULL) return;
    _destroyBNode(node->left);
    _destroyBNode(node->right);
    free(node);
}

void destroyBinaryTree(BinaryTree *tree) {
    _destroyBNode(tree->root);
    free(tree);
}

void _destroyBNodeDeep(BNode *node) {
    if (node == NULL) return;
    _destroyBNodeDeep(node->left);
    _destroyBNodeDeep(node->right);
    free((char *) node->data);
    free(node);
}

void destroyBinaryTreeDeep(BinaryTree *tree) {
    if (tree == NULL) return;
    _destroyBNodeDeep(tree->root);
    free(tree);
}


int _findMinNodeBT(BNode *node, BNode ***result, int *size) {
    BNode *parent;
    while (node != NULL) {
        parent = node;
        node = node->left;
    }
    int minKey = parent->key;
    while (parent->parent != NULL && parent->parent->key == minKey) {
        parent = parent->parent;
    }
    *result = malloc(sizeof(BNode *) * (parent->generation + 1));
    *size = parent->generation + 1;
    while (parent != NULL) {
        (*result)[parent->generation] = parent;
        parent = parent->left;
    }
    return 0;
}


int addBT(BinaryTree *tree, unsigned int key, const char *data) {
    if (tree == NULL) return 1;
    BNode *newNode = getBNode(key, data);
    if (tree->root == NULL) {
        tree->root = newNode;
        return 0;
    }
    BNode *ptr = tree->root;
    BNode *parent;
    while (ptr != NULL) {
        parent = ptr;
        if (ptr->key >= key) {
            if (ptr->key == key) ptr->generation++;
            ptr = ptr->left;
        } else {
            ptr = ptr->right;
        }
    }
    newNode->parent = parent;
    if (parent->key >= key) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    return 0;
}


int deleteBT(BinaryTree *tree, unsigned int key) {
    int size;
    BNode **targetsArray;

    int findRes = findBT(tree, key, &targetsArray, &size);
    if (findRes) return findRes;
    BNode *target = targetsArray[size - 1];
    free(targetsArray);
//    _swapRoutes(target);
    if (target->left == NULL && target->right == NULL) {
        if (tree->root == target) {
            tree->root = NULL;
            free((char *) target->data);
            free(target);
            return 0;
        }
        if (target->parent->left == target) {
            target->parent->left = NULL;
        } else {
            target->parent->right = NULL;
        }
        free((char *) target->data);
        free(target);
        return 0;
    }
    if (target->left == NULL) { // target->right != NULL
        if (tree->root == target) {
            tree->root = target->right;
            target->right->parent = NULL;
            free((char *) target->data);
            free(target);
            return 0;
        }
        if (target->parent->left == target) {
            target->parent->left = target->right;
        } else {
            target->parent->right = target->right;
        }
        target->right->parent = target->parent;
        free((char *) target->data);
        free(target);
        return 0;
    }
    if (target->right == NULL) { // target->left != NULL
        if (tree->root == target) {
            tree->root = target->left;
            target->left->parent = NULL;
            free((char *) target->data);
            free(target);
            return 0;
        }
        if (target->parent->left == target) {
            target->parent->left = target->left;
        } else {
            target->parent->right = target->left;
        }
        target->left->parent = target->parent;
        free((char *) target->data);
        free(target);
        return 0;
    }
    // target->right != NULL && target->left != NULL
    BNode **minData;
    int minDataSize = 0;
    _findMinNodeBT(target->right, &minData, &minDataSize);
    BNode *victim = minData[minDataSize - 1];
    free(minData);
    if (victim->parent != target && victim->parent->left == victim) {
        if (minDataSize == 1) {
            victim->parent->left = NULL;
        } else {
            victim->parent->left = victim->right;
            victim->right->parent = victim->parent;
        }
    }

    if (victim->parent != target) {
        victim->right = target->right;
        target->right->parent = victim;
    }
    if (victim->parent == target && victim->left != NULL || minDataSize != 1) {
        BNode *ptr = victim->left;
        BNode *parent;
        while (ptr != NULL) {
            parent = ptr;
            ptr = ptr->left;
        }
        target->left->parent = parent;
        parent->left = target->left;
    } else {
        victim->left = target->left;
        target->left->parent = victim;
    }
    if (target->parent != NULL) {
        if (target->parent->left == target) {
            target->parent->left = victim;
        } else {
            target->parent->right = victim;
        }
        victim->parent = target->parent;
    }
    if (tree->root == target) {
        tree->root = victim;
        victim->parent = NULL;
    }
    free((char *) target->data);
    free(target);
    return 0;
}

void _simplePrint(BNode *node, int space) {
    if (node == NULL) return;
    space += 5;
    _simplePrint(node->right, space);
    printf("\n");
    for (int i = 5; i < space; i++)
        printf(" ");
    printf("%d.%d \n", node->key, node->generation);
    _simplePrint(node->left, space);
}

int printNLR_BT(const BinaryTree *tree) {
    if (tree == NULL) return 1;
    _simplePrint(tree->root, 0);
    return 0;
}

int writeNLR_BT(const BinaryTree *tree, DrawMode mode) {
    if (tree == NULL) return 1;
    createPngGraph(tree, mode);
    return 0;
}

int findBT(const BinaryTree *tree, unsigned int key, BNode ***result, int *size) {
    if (tree == NULL || tree->root == NULL) return 1;
    BNode *ptr = tree->root;
    int found = 0;
    while (ptr != NULL) {
        if (ptr->key == key) {
            if (!found) {
                *result = malloc(sizeof(BNode *) * (ptr->generation + 1));
                *size = ptr->generation + 1;
                found = 1;
            }
            (*result)[ptr->generation] = ptr;
            if (ptr->generation == 0) return 0;
        }
        if (ptr->key >= key) {
            ptr = ptr->left;
        } else {
            ptr = ptr->right;
        }
    }
    if (found == 0) return 1;
    return 0;
}

int findMinBT(const BinaryTree *tree, BNode ***result, int *size) {
    if (tree == NULL || tree->root == NULL) return 1;
    return _findMinNodeBT(tree->root, result, size);
}


