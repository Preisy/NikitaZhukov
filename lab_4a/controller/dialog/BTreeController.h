#ifndef DIALOG_H
#define DIALOG_H

#include "GraphGenerator.h"

enum ExecutionCode {
    Ok,
    CommandError,
    ExecutionError,
    NotFound
};

void C_add(BinaryTree* tree, char* args, enum ExecutionCode* responseCode);

void C_del(BinaryTree* tree, char* args, enum ExecutionCode* responseCode);

void C_tr(BinaryTree* tree, char* args, enum ExecutionCode* responseCode);

void C_find(BinaryTree* tree, char* args, enum ExecutionCode* responseCode, BNode ***result, int *size);

void C_findMin(BinaryTree* tree, char* args, enum ExecutionCode* responseCode, BNode ***result, int *size);

BinaryTree* C_file(char* args, enum ExecutionCode* responseCode);

void C_write(BinaryTree* tree, char* args, enum ExecutionCode* responseCode);

void C_print(BinaryTree* tree, char* args, enum ExecutionCode* responseCode);


#endif
