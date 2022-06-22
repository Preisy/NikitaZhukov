#define  _GNU_SOURCE

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "Tree.h"
#include "Graph.h"

Tree* getTree() {
    return calloc(1, sizeof(Tree));
}

Tree* getTreeFromFile(char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) return NULL;

    Tree* tree = getTree();

    char* line = NULL;
    while (!feof(file)) {
        unsigned int key;
        size_t len;

        if (fscanf(file, "%d\n", &key) <= 0) break;
        if (getline(&line, &len, file) <= 0) break;

        char* data = malloc(len + 1);
        strcpy(data, line);

        addTree(tree, key, data);
    }

    free(line);
    fclose(file);

    return tree;
}


void _NodeDestructorDeep(Node* node) {
    if (node == NULL) return;

    _NodeDestructorDeep(node->left);
    _NodeDestructorDeep(node->right);

    free((char*) node->data);
    free(node);
}

void treeDestructorDeep(Tree* tree) {
    if (tree == NULL) return;

    _NodeDestructorDeep(tree->root);
    free(tree);
}


int _findMinNodeTree(Node* node, Node*** res, int* len) {
    Node* parent;

    while (node != NULL) {
        parent = node;
        node = node->left;
    }

    int minKey = parent->key;
    while (parent->parent != NULL && parent->parent->key == minKey) {
        parent = parent->parent;
    }

    *res = malloc(sizeof(Node*) * (parent->version + 1));
    *len = parent->version + 1;
    while (parent != NULL) {
        (*res)[parent->version] = parent;
        parent = parent->left;
    }

    return 0;
}


int addTree(Tree* tree, int key, char* data) {
    if (tree == NULL) return 1;

    Node* newNode = getNode(key, data);
    if (tree->root == NULL) {
        tree->root = newNode;
        return 0;
    }

    Node* it = tree->root;
    Node* parent;
    while (it != NULL) {
        parent = it;

        if (it->key >= key) {
            if (it->key == key) it->version++;

            it = it->left;
        } else {
            it = it->right;
        }
    }

    newNode->parent = parent;
    if (parent->key >= key) parent->left = newNode;
    else parent->right = newNode;

    return 0;
}


int deleteTree(Tree* tree, int key) {
    int size;
    Node** targetsArray;

    int findRes = findTree(tree, key, &targetsArray, &size);
    if (findRes) return findRes;
    Node* target = targetsArray[size - 1];
    free(targetsArray);

    if (target->left == NULL && target->right == NULL) {
        if (tree->root == target) {
            tree->root = NULL;
            free((char*) target->data);
            free(target);
            return 0;
        }
        if (target->parent->left == target) {
            target->parent->left = NULL;
        } else {
            target->parent->right = NULL;
        }
        free((char*) target->data);
        free(target);
        return 0;
    }
    if (target->left == NULL) {
        if (tree->root == target) {
            tree->root = target->right;
            target->right->parent = NULL;
            free((char*) target->data);
            free(target);
            return 0;
        }
        if (target->parent->left == target) {
            target->parent->left = target->right;
        } else {
            target->parent->right = target->right;
        }
        target->right->parent = target->parent;
        free((char*) target->data);
        free(target);
        return 0;
    }
    if (target->right == NULL) {
        if (tree->root == target) {
            tree->root = target->left;
            target->left->parent = NULL;
            free((char*) target->data);
            free(target);
            return 0;
        }
        if (target->parent->left == target) {
            target->parent->left = target->left;
        } else {
            target->parent->right = target->left;
        }
        target->left->parent = target->parent;
        free((char*) target->data);
        free(target);
        return 0;
    }

    Node** minData;
    int minDataSize = 0;
    _findMinNodeTree(target->right, &minData, &minDataSize);
    Node* victim = minData[minDataSize - 1];
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
        Node* ptr = victim->left;
        Node* parent;
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
    free((char*) target->data);
    free(target);
    return 0;
}

void _recPrintTree(Node* node, int space) {
    if (node == NULL) return;
    space += 6;

    _recPrintTree(node->right, space);
    printf("\n");

    for (int i = 6; i < space; i++) printf(" ");
    printf("%d (%d) \n", node->key, node->version);

    _recPrintTree(node->left, space);
}

int printTree(Tree* tree) {
    if (tree == NULL)
        return 1;

    _recPrintTree(tree->root, 0);
    return 0;
}

int writeTree(Tree* tree, DrawMode mode) {
    if (tree == NULL)
        return 1;

    createGraph(tree, mode);
    return 0;
}

int findTree(Tree* tree, int key, Node*** res, int* len) {
    Node* it = tree->root;
    int count = 0;

    while (it != NULL) {
        if (it->key == key) {
            if (!count) {
                *res = malloc(sizeof(Node*) * (it->version + 1));
                *len = it->version + 1;
                count = 1;
            }

            (*res)[it->version] = it;
            if (it->version == 0)
                return 0;
        }

        if (it->key >= key) it = it->left;
        else it = it->right;
    }

    if (count == 0)
        return 1;

    return 0;
}

int findMinTree(Tree* tree, Node*** res, int* len) {
    if (tree == NULL) return 1;

    return _findMinNodeTree(tree->root, res, len);
}

void _recTraversalTree(const Node* node) {
    if (node == NULL) return;

    printf("%d: %s (%d)\n", node->key, node->data, node->version);

    _recTraversalTree(node->left);
    _recTraversalTree(node->right);
}

int traversalTree(Tree* tree) {
    if (tree == NULL) return 0;
    _recTraversalTree(tree->root);
    return 0;
}



