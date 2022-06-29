#ifndef DIALOG_H
#define DIALOG_H

#include "Tree.h"

enum ExecutionCode {
    Ok,
    CommandError,
    ExecutionError,
    NotFound
};

void C_mock(Tree* tree, char* args, enum ExecutionCode* responseCode);

void C_add(Tree* tree, char* args, enum ExecutionCode* responseCode);

void C_del(Tree* tree, char* args, enum ExecutionCode* responseCode);

void C_tr(Tree* tree, char* args, enum ExecutionCode* responseCode);

void C_find(Tree* tree, char* args, enum ExecutionCode* responseCode, Node*** result, int* size);

void C_sfind(Tree* tree, char* args, enum ExecutionCode* responseCode, Node*** result, int* size);

Tree* C_file(char* args, enum ExecutionCode* responseCode);

void C_write(Tree* tree, char* args, enum ExecutionCode* responseCode);

void C_print(Tree* tree, char* args, enum ExecutionCode* responseCode);


#endif
