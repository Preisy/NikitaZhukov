#include <stdlib.h>
#include <string.h>
#include "TreeController.h"

char* _getString(char* str) {
    char* res = (char*) malloc(sizeof(char) * (strlen(str) + 1));
    memcpy(res, str, sizeof(char) * strlen(str));
    res[strlen(str)] = '\0';
    return res;
}

void C_mock(Tree* tree, char* args, enum ExecutionCode* responseCode) {
    *responseCode = Ok;

    if (strcmp(args, "") != 0) {
        *responseCode = CommandError;
        return;
    }

    if (addTree(tree, _getString("15"), _getString("")))
        *responseCode = ExecutionError;
    if (addTree(tree, _getString("20"), _getString("")))
        *responseCode = ExecutionError;
    if (addTree(tree, _getString("10"), _getString("")))
        *responseCode = ExecutionError;
    if (addTree(tree, _getString("30"), _getString("")))
        *responseCode = ExecutionError;
    if (addTree(tree, _getString("40"), _getString("")))
        *responseCode = ExecutionError;
    if (addTree(tree, _getString("5"), _getString("")))
        *responseCode = ExecutionError;
    if (addTree(tree, _getString("1"), _getString("")))
        *responseCode = ExecutionError;
    if (addTree(tree, _getString("7"), _getString("")))
        *responseCode = ExecutionError;
}

void C_add(Tree* tree, char* args, enum ExecutionCode* responseCode) {
    *responseCode = Ok;

    int i = 0;
    for (; i < strlen(args); ++i) {
        if (args[i] == ' ')
            break;
    }

    char* key = "";
    char* data = "";

    key = (char*) calloc(i + 1, sizeof (char));
    memcpy(key, args, sizeof (char) * i);
    key[i] = '\0';

    if (strlen(args) > i + 1) {
        data = (char*) calloc(strlen(args) - i, sizeof(char));
        memcpy(data, args + i + 1, sizeof(char) * (strlen(args) - i - 1));
        data[strlen(args) - i - 1] = '\0';
    } else {
        data = (char*) calloc(1, sizeof(char));
        data[0] = '\0';
    }

    if (addTree(tree, key, data) == 1) {
        *responseCode = ExecutionError;
    }
}

void C_del(Tree* tree, char* args, enum ExecutionCode* responseCode) {
    *responseCode = Ok;

    int i = 0;
    for (; i < strlen(args); ++i) {
        if (args[i] == ' ') {
            *responseCode = CommandError;
            return;
        }
    }

    char* key = "";

    key = (char*) calloc(i + 1, sizeof (char));
    memcpy(key, args, sizeof (char) * i);
    key[i] = '\0';


    if (deleteTree(tree, key)) {
        *responseCode = NotFound;
    }
    free(key);
}

void C_tr(Tree* tree, char* args, enum ExecutionCode* responseCode) {
    *responseCode = Ok;

    if (strcmp(args, "") != 0) {
        *responseCode = CommandError;
        return;
    }
    if (traversalTree(tree)) {
        *responseCode = ExecutionError;
    }
}

void C_find(Tree* tree, char* args, enum ExecutionCode* responseCode, Node*** result, int* size) {
    *responseCode = Ok;

    int i = 0;
    for (; i < strlen(args); ++i) {
        if (args[i] == ' ') {
            *responseCode = CommandError;
            return;
        }
    }

    char* key = "";

    key = (char*) calloc(i + 1, sizeof (char));
    memcpy(key, args, sizeof (char) * i);
    key[i] = '\0';

    if (findTree(tree, key, result, size)) {
        *responseCode = NotFound;
    }
    free(key);
}

void C_findMin(Tree* tree, char* args, enum ExecutionCode* responseCode, Node*** result, int* size) {
    *responseCode = Ok;

    if (strcmp(args, "") != 0) {
        *responseCode = CommandError;
        return;
    }
    if (findMinTree(tree, result, size)) {
        *responseCode = ExecutionError;
    }
}

Tree* C_file(char* args, enum ExecutionCode* responseCode) {
    *responseCode = Ok;
    Tree* res = getTreeFromFile(args);
    if (res == NULL)
        *responseCode = ExecutionError;
    return res;
}

void C_write(Tree* tree, char* args, enum ExecutionCode* responseCode) {
    *responseCode = Ok;

    if (strcmp(args, "-p") == 0) {
        if (writeTree(tree, Parent) == 1) {
            *responseCode = ExecutionError;
        }
    } else if (strcmp(args, "") == 0) {
        if (writeTree(tree, Default) == 1) {
            *responseCode = ExecutionError;
        }
    } else {
        *responseCode = CommandError;
    }
}

void C_print(Tree* tree, char* args, enum ExecutionCode* responseCode) {
    *responseCode = Ok;

    if (strcmp(args, "") != 0) {
        *responseCode = CommandError;
        return;
    }
    if (printTree(tree)) {
        *responseCode = ExecutionError;
    }
}