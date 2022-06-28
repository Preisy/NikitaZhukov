#ifndef DIALOG_H
#define DIALOG_H

#include "Graph.h"

enum ExecutionCode {
    Ok,
    CommandError,
    ExecutionError,
    NotFound
};

void C_addv(Graph* graph, char* args, enum ExecutionCode* responseCode);
void C_adde(Graph* graph, char* args, enum ExecutionCode* responseCode);
void C_delv(Graph* graph, char* args, enum ExecutionCode* responseCode);
void C_dele(Graph* graph, char* args, enum ExecutionCode* responseCode);
void C_find(Graph* graph, char* args, enum ExecutionCode* responseCode);
void C_sfind(Graph* graph, char* args, enum ExecutionCode* responseCode);
void C_print(Graph* graph, char* args, enum ExecutionCode* responseCode);

#endif
