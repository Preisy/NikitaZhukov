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

    while (!feof(file)) {
        char bufKey[80];
        char bufData[80];

        if (fscanf(file, "%s\n", bufKey) <= 0) break;
        if (fscanf(file, "%s\n", bufData) <= 0) break;

        char* key = malloc(strlen(bufKey) + 1);
        strcpy(key, bufKey);

        char* data = malloc(sizeof(bufData) + 1);
        strcpy(data, bufData);

        addTree(tree, key, data);
    }

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

void _setLeft(Node* this, Node* left) {
    this->left = left;
    if (left != NULL)
        left->parent = this;
}


void _setRight(Node*this, Node* right) {
    this->right = right;
    if (right != NULL)
        right->parent = this;
}

void rightTurn(Tree* this, Node* node) {
    Node* left = node->left;
    Node* lr = node->left->right;
    if (node->parent == NULL) {
        this->root = node->left;
        node->left->parent = NULL;
    } else if (node->parent->right == node) {
        _setRight(node->parent, left);
    } else if (node->parent->left == node) {
        _setLeft(node->parent, left);
    }
    _setLeft(node, lr);
    _setRight(left, node);
}

void leftTurn(Tree* this, Node* node) {
    Node* right = node->right;
    Node* rl = node->right->left;
    if (node->parent == NULL) {
        this->root = node->right;
        node->right->parent = NULL;
    } else if (node->parent->right == node) {
        _setRight(node->parent, right);
    } else if (node->parent->left == node) {
        _setLeft(node->parent, right);
    }
    _setRight(node, rl);
    _setLeft(right, node);
}

int balanceNode(Tree* this, Node** parent) {
    if ((*parent)->balance == 2) {
        if ((*parent)->right != NULL && (*parent)->right->balance == 1) {
            Node* a = *parent;
            Node* b = (*parent)->right;
            leftTurn(this, a);
            a->balance = 0;
            b->balance = 0;
            (*parent) = b;
        } else {
            Node* a = *parent;
            Node* b = (*parent)->right;
            Node* c = (*parent)->right->left;
            rightTurn(this, (*parent)->right);
            leftTurn(this, *parent);

            if (b->balance == 0) {
                a->balance = 0;
                b->balance = 1;
                c->balance = 1;
            } else if (c->balance == 0) {
                a->balance = 0;
                int bBalance = b->balance;
                if (bBalance == -1) {
                    b->balance = 0;
                    c->balance = 0;
                } else if (bBalance == 0) {
                    b->balance = 1;
                    c->balance = 1;
                }
            } else if (c->balance == -1) {
                a->balance = 0;
                b->balance = 1;
                c->balance = 0;
            } else if (c->balance == 1) {
                a->balance = -1;
                b->balance = 0;
                c->balance = 0;
            }

            *parent = c;
        }
        return 0;
    } else if ((*parent)->balance == -2) {
        if ((*parent)->left != NULL && (*parent)->left->balance == -1) {
            Node* a = *parent;
            Node* b = (*parent)->left;
            rightTurn(this, a);
            a->balance = 0;
            b->balance = 0;
            *parent = b;
        } else {
            Node* a = *parent;
            Node* b = (*parent)->left;
            Node* c = (*parent)->left->right;
            leftTurn(this, (*parent)->left);
            rightTurn(this, *parent);

            if (b->balance == 0) {
                a->balance = 0;
                b->balance = -1;
                c->balance = -1;
            } else if (c->balance == 0) {
                a->balance = 0;
                int bBalance = b->balance;
                if (bBalance == 1) {
                    b->balance = 0;
                    c->balance = 0;
                } else if (bBalance == 0) {
                    b->balance = -1;
                    c->balance = -1;
                }
            } else if (c->balance == -1) {
                a->balance = 1;
                b->balance = 0;
                c->balance = 0;
            } else if (c->balance == 1) {
                a->balance = 0;
                b->balance = -1;
                c->balance = 0;
            }
            *parent = c;
        }
        return 0;
    }
    return 1;
}






void _addingCorrect(Tree* this, Node* el) {
    Node* node = el;
    for (Node* parent = el->parent; parent != NULL; parent = parent->parent) {
        if (parent->left == node) {
            parent->balance = parent->balance - 1;
        } else if (parent->right == node) {
            parent->balance = parent->balance + 1;
        }

        balanceNode(this, &parent);

        if (parent->balance == 0)
            return;

        node = parent;
    }
}


int addTree(Tree* this, char* key, char* data) {
    if (this->root == NULL) {
        this->root = getNode(key, data);
        return 0;
    }
    Node* it = this->root;
    while (1) {
        if (strcmp(key, it->key) == 0) {
            it->data = data;
            return 0;
        } else if (strcmp(key, it->key) > 0) {
            if (it->right == NULL) {
                _setRight(it, getNode(key, data));
                _addingCorrect(this, it->right);
                return 0;
            }
            it = it->right;
        } else {
            if (it->left == NULL) {
                _setLeft(it, getNode(key, data));
                _addingCorrect(this, it->left);
                return 0;
            }
            it = it->left;
        }
    }
    return 1;
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




int getSide(Node* node) {
    if (node->parent == NULL) {
        return -2;
    } else if (node->parent->left == node) {
        return -1;
    } else if (node->parent->right == node) {
        return 1;
    } else {
        exit(-2);
    }
}


void deletingCorrect(Tree* this, Node* el, int side) {
    if (el == NULL)
        return;
    if (side == -2) {
        return;
    }

    for (Node* node = el; node != NULL; node = node->parent) {
        if (node->balance == 0) {
            node->balance = node->balance - side;
            return;
        }
        node->balance = node->balance - side;

        balanceNode(this, &node);
        if (node->balance == -1) {
            return;
        } else if (node->balance == 1) {
            return;
        }
        if (node->parent != NULL) {
            side = getSide(node);
        }
    }
}


int deleteTree(Tree* this, char* key) {
    Node* node = _findNode(this, key);
    if (node == NULL) return 1;

    if (strcmp(key, "10") == 0) {
        int a = 0;
    }

    if (node->right == NULL) {
        Node* parent = node->parent;
        int side = getSide(node);
        _replaceNode(this, node, node->left);
        if (parent != NULL) {
            deletingCorrect(this, parent, side);
        }
        _nodeDestructor(node);
        return 0;
    }
    Node* it = node->right;
    while (it->left != NULL)
        it = it->left;

    Node* parent = it->parent;
    int side = getSide(it);

    _replaceNode(this, it, it->right);
    _moveEntry(node, it);

    if (parent != NULL) {
        deletingCorrect(this, parent, side);
    }

    _nodeDestructor(it);

    return 0;
}


int _sFind(Node* node, Node*** res, int* len) {
    Node* minNode;
    Node* el = node;
    while (el != NULL) {
        minNode = el;
        el = el->left;
    }

    Node* maxNode;
    el = node;
    while (el != NULL) {
        maxNode = el;
        el = el->right;
    }

    char* minKey = minNode->key;
    while (minNode->parent != NULL && strcmp(minNode->parent->key, minKey) == 0) {
        minNode = minNode->parent;
    }

    *res = malloc(sizeof(Node*) * (2));
    *len = 2;

    (*res)[0] = minNode;
    (*res)[1] = maxNode;

    return 0;
}


int sFindTree(Tree* tree, Node*** res, int* len) {
    if (tree == NULL) return 1;

    return _sFind(tree->root, res, len);
}

void _recTraversalTree(const Node* node, char* min, char* max) {
    if (node == NULL) return;
    if (strcmp(node->key, min) < 0 || strcmp(node->key, max) > 0) return;


    _recTraversalTree(node->left, min, max);
    _recTraversalTree(node->right, min, max);

    printf("%s: %s\n", node->key, node->data);
}

int traversalTree(Tree* tree, char* min, char* max) {
    if (tree == NULL) return 0;

    _recTraversalTree(tree->root, min, max);
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
