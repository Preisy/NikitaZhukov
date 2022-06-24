#define  _GNU_SOURCE

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "Tree.h"

Tree* getTree() {
    return calloc(1, sizeof(Tree));
}

Tree* getTreeFromFile(char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) return NULL;

    Tree* tree = getTree();

    char* line = NULL;
    while (!feof(file)) {
        char bufKey[80];
        size_t len;

        if (fscanf(file, "%s\n", bufKey) <= 0) break;
        if (getline(&line, &len, file) <= 0) break;

        char* key = malloc(strlen(bufKey) + 1);
        strcpy(key, bufKey);

        char* data = malloc(len + 1);
        strcpy(data, line);

        addTree(tree, key, data);
    }

    free(line);
    fclose(file);

    return tree;
}

void _nodeDestructor(Node* node) {
    free(node->data);
    free(node->key);
    free(node);
}

void _nodeDestructorDeep(Node* node) {
    if (node == NULL) return;

    _nodeDestructorDeep(node->left);
    _nodeDestructorDeep(node->right);

    _nodeDestructor(node);
}

void treeDestructor(Tree* tree) {
    if (tree == NULL) return;

    _nodeDestructorDeep(tree->root);
    free(tree);
}

int findTree(Tree* tree, char* key, Node*** res, int* len) {
    Node* it = tree->root;
    int count = 0;

    while (it != NULL) {
        if (strcmp(it->key, key) == 0) {
            if (!count) {
                *res = malloc(sizeof(Node*) * (it->version + 1));
                *len = it->version + 1;
                count = 1;
            }

            (*res)[it->version] = it;
            if (it->version == 0)
                return 0;
        }

        if (strcmp(it->key, key) >= 0) it = it->left;
        else it = it->right;
    }

    if (count == 0)
        return 1;

    return 0;
}

int addTree(Tree* tree, char* key, char* data) {
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

        if (strcmp(it->key, key) >= 0) {
            if (strcmp(it->key, key) == 0) it->version++;

            it = it->left;
        } else {
            it = it->right;
        }
    }

    newNode->parent = parent;
    if (strcmp(parent->key, key) >= 0) parent->left = newNode;
    else parent->right = newNode;

    return 0;
}

void _moveEntry(Node* this, Node* node) {
    free(this->data);
    free(this->key);

    this->key = node->key;
    this->data = node->data;
    this->version = node->version;

    node->key = NULL;
    node->data = NULL;
    node->version = -1;
}

Node* _replaceNode(Tree* this, Node* oldNode, Node* newNode) {
    if (oldNode->parent == NULL) {
        this->root = newNode;
    } else if (oldNode->parent->left != NULL &&
               oldNode->parent->left->key == oldNode->key)
        oldNode->parent->left = newNode;
    else if (oldNode->parent->right != NULL &&
             oldNode->parent->right->key == oldNode->key)
        oldNode->parent->right = newNode;

    if (newNode != NULL)
        newNode->parent = oldNode->parent;

    return newNode;
}

Node* _findNode(Tree* this, char* key) {
    Node* it = this->root;
    while (it != NULL) {
        if (strcmp(it->key, key) == 0) {
            return it;
        } else if (strcmp(it->key, key) > 0) {
            it = it->left;
        } else {
            it = it->right;
        }
    }
    return NULL;
}

int deleteTree(Tree* this, char* key) {
    Node* node = _findNode(this, key);
    if (node == NULL) return 1;

    if (node->right == NULL) {
        _replaceNode(this, node, node->left);
        _nodeDestructor(node);
        return 0;
    }
    Node* it = node->right;
    while (it->left != NULL)
        it = it->left;

    _replaceNode(this, it, it->right);
    _moveEntry(node, it);
    _nodeDestructor(it);

    return 0;
}


int _findMinNodeTree(Node* node, Node*** res, int* len) {
    Node* parent;

    while (node != NULL) {
        parent = node;
        node = node->left;
    }

    char* minKey = parent->key;
    while (parent->parent != NULL && strcmp(parent->parent->key, minKey) == 0) {
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


int findMinTree(Tree* tree, Node*** res, int* len) {
    if (tree == NULL) return 1;

    return _findMinNodeTree(tree->root, res, len);
}

void _recTraversalTree(const Node* node) {
    if (node == NULL) return;

    printf("%s: %s\n", node->key, node->data);

    _recTraversalTree(node->left);
    _recTraversalTree(node->right);
}

int traversalTree(Tree* tree) {
    if (tree == NULL) return 0;

    _recTraversalTree(tree->root);
    return 0;
}


void _recWrite(FILE* file, Node* node, int* leaves, DrawMode mode) {
    if (node == NULL) return;
    if (node->left == NULL) {
        fprintf(file, "\"%s: %s\"->null%d[style=invis];", node->key, node->data, *leaves);
        (*leaves)++;
    } else {
        fprintf(file, "\"%s: %s\"->\"%s: %s\";", node->key, node->data,
                node->left->key, node->left->data);
        if (mode == Parent)
            fprintf(file, "\"%s: %s\"->\"%s: %s\";", node->left->key, node->left->data,
                    node->left->parent->key, node->left->parent->data);

    }
    if (node->right == NULL) {
        fprintf(file, "\"%s: %s\"->null%d[style=invis];", node->key, node->data, *leaves);
        (*leaves)++;
    } else {
        fprintf(file, "\"%s: %s\"->\"%s: %s\";", node->key, node->data,
                node->right->key, node->right->data);
        if (mode == Parent)
            fprintf(file, "\"%s: %s\"->\"%s: %s\";", node->right->key, node->right->data,
                    node->right->parent->key, node->right->parent->data);

    }
    _recWrite(file, node->left, leaves, mode);
    _recWrite(file, node->right, leaves, mode);
}

int createGraph(Tree* tree, DrawMode mode) {
    if (tree == NULL)
        return 1;

    FILE* file = fopen("./tree.dot", "w");
    if (file == NULL) return 1;

    fprintf(file, "digraph binaryTree {node[shape=circle,color=black,fontcolor=black,fontsize=10];");
    int count = 0;

    if (tree->root != NULL) {
        fprintf(file, "\"%s: %s\"", tree->root->key, tree->root->data);
        _recWrite(file, tree->root, &count, mode);
        for (int i = 0; i < count; ++i) {
            fprintf(file, "null%d[style=invis];", i);
        }
    }

    fprintf(file, "}");
    fclose(file);

    system("dot -Tpng -O ./tree.dot");
    remove("./tree.dot");
    return 0;
}

void _recPrintTree(Node* node, int space) {
    if (node == NULL) return;
    space += 6;

    _recPrintTree(node->right, space);
    printf("\n");

    for (int i = 6; i < space; i++) printf(" ");
    printf("%s: %s\n", node->key, node->data);

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
