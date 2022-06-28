#ifndef LAB_4A_DIALOG_H
#define LAB_4A_DIALOG_H

#include "stdio.h"
#include "string.h"

typedef struct Response {
    char command[256];
    char args[256];
} Response;

void ask(Response* response);

void help();

#endif //LAB_4A_DIALOG_H
