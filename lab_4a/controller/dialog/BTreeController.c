#include <stdlib.h>
#include <string.h>
#include "BTreeController.h"

int validate(char sym) {
    if ('0' <= sym && sym <= '9')
        return 1;
    else
        return 0;
}

int convertToInt(char* begin, char* end, int* res) {
    *res = 0;
    for (; begin != end; ++begin) {
        if (validate(*begin))
            *res = *res * 10 + (*begin - '0');
        else
            return 1;
    }

    return 0;
}


void C_add(BinaryTree* tree, char* args, enum ExecutionCode* responseCode) {
    *responseCode = Ok;

    int i = 0;
    for (; i < strlen(args); ++i) {
        if (args[i] == ' ')
            break;
    }

    int key = -1;
    char* data = "";

    if (convertToInt(args, args + i, &key)) {
        *responseCode = CommandError;
        return;
    }
    if (strlen(args) > i + 1) {
        data = (char*) calloc(strlen(args) - i, sizeof (char));
        memcpy(data, args + i + 1, sizeof (char) * (strlen(args) - i - 1));
        data[strlen(args) - i - 1] = '\0';
    } else {
        data = (char*) calloc(1, sizeof (char));
        data[0] = '\0';
    }

    if (addBT(tree, key, data) == 1) {
        *responseCode = ExecutionError;
    }
}

void C_del(BinaryTree* tree, char* args, enum ExecutionCode* responseCode) {
    *responseCode = Ok;
    int n;
    if (convertToInt(args, args + strlen(args), &n)) {
        *responseCode = CommandError;
        return;
    }

    if (deleteBT(tree, n)) {
        *responseCode = ExecutionError;
    }
}

void C_tr(BinaryTree* tree, char* args, enum ExecutionCode* responseCode) {
    *responseCode = Ok;

    if (strcmp(args, "") != 0) {
        *responseCode = CommandError;
        return;
    }
    if (traversalBT(tree)) {
        *responseCode = ExecutionError;
    }
}

void C_find(BinaryTree* tree, char* args, enum ExecutionCode* responseCode, BNode ***result, int *size) {
    *responseCode = Ok;
    int n;
    if (convertToInt(args, args + strlen(args), &n)) {
        *responseCode = CommandError;
        return;
    }

    if (findBT(tree, n, result, size)) {
        *responseCode = NotFound;
    }
}

void C_findMin(BinaryTree* tree, char* args, enum ExecutionCode* responseCode, BNode ***result, int *size) {
    *responseCode = Ok;

    if (strcmp(args, "") != 0) {
        *responseCode = CommandError;
        return;
    }
    if (findMinBT(tree, result, size)) {
        *responseCode = ExecutionError;
    }
}

BinaryTree* C_file(char* args, enum ExecutionCode* responseCode) {
    *responseCode = Ok;
    BinaryTree* res = getBinaryTreeFromFile(args);
    if (res == NULL)
        *responseCode = ExecutionError;
    return res;
}

void C_write(BinaryTree* tree, char* args, enum ExecutionCode* responseCode) {
    *responseCode = Ok;

    if (strcmp(args, "-p") == 0) {
        if (writeNLR_BT(tree, PARENT) == 1) {
            *responseCode = ExecutionError;
        }
    } else if (strcmp(args, "") == 0) {
        if (writeNLR_BT(tree, DEFAULT) == 1) {
            *responseCode = ExecutionError;
        }
    } else {
        *responseCode = CommandError;
    }
}

void C_print(BinaryTree* tree, char* args, enum ExecutionCode* responseCode) {
    *responseCode = Ok;

    if (strcmp(args, "") != 0) {
        *responseCode = CommandError;
        return;
    }
    if (printNLR_BT(tree)) {
        *responseCode = ExecutionError;
    }
}