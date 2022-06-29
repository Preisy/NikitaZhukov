#include "controller/TreeController.h"
#include "Dialog.h"
#include "string.h"
#include "stdlib.h"


int main() {
    Tree* tree = getTree();

    Response response = {"", ""};
    printf("Type your command or type help\n");
    while (strcmp(response.command, "exit") != 0) {
        ask(&response);

        enum ExecutionCode executionCode;
        if (strcmp(response.command, "exit") == 0) {
            break;
        } else if (strcmp(response.command, "help") == 0) {
            help();
            executionCode = Ok;
        } else if (strcmp(response.command, "add") == 0) {
            C_add(tree, response.args, &executionCode);
        } else if (strcmp(response.command, "del") == 0) {
            C_del(tree, response.args, &executionCode);
        } else if (strcmp(response.command, "tr") == 0) {
            C_tr(tree, response.args, &executionCode);
        } else if (strcmp(response.command, "find") == 0) {
            Node** res;
            int size;
            C_find(tree, response.args, &executionCode, &res, &size);
            if (executionCode == Ok) {
                for (int i = 0; i < size; ++i) {
                    printf("%s %s\n", res[i]->key, res[i]->data);
                }
                free(res);
            }
        } else if (strcmp(response.command, "sfind") == 0) {
            Node** res;
            int size;
            C_sfind(tree, response.args, &executionCode, &res, &size);
            if (executionCode == Ok) {
                for (int i = 0; i < size; ++i) {
                    printf("%s %s\n", res[i]->key, res[i]->data);
                }
                free(res);
            }
        } else if (strcmp(response.command, "file") == 0) {
            Tree* tmp = C_file(response.args, &executionCode);
            if (tmp != NULL) {
                treeDestructor(tree);
                tree = tmp;
            }
        } else if (strcmp(response.command, "write") == 0) {
            C_write(tree, response.args, &executionCode);
        } else if (strcmp(response.command, "print") == 0) {
            C_print(tree, response.args, &executionCode);
        } else if (strcmp(response.command, "mock") == 0) {
            C_mock(tree, response.args, &executionCode);
        } else {
            executionCode = CommandError;
        }


        if (executionCode == CommandError) {
            printf("Incorrect command <%s>. Try again\n", response.command);
            continue;
        } else if (executionCode == ExecutionError) {
            printf("Execution error <%s>\n", response.command);
            continue;
        } else if (executionCode == NotFound) {
            printf("Not Found\n");
            continue;
        }
    }


    treeDestructor(tree);
    return 0;
}
