#include "Dialog.h"
#include "string.h"

void ask(Response* response) {
    request:
    for (int i = 0; i < 256; ++i)
        response->command[i] = response->args[i] = '\0';
    printf("\033[34m>>> \033[36m");

    char input[256] = {'\0'};
    if (fgets(input, sizeof(input), stdin) == NULL || strlen(input) == 1) {
        printf("\033[0m");
        printf("Incorrect command. Try again\n");
        while (getc(stdin) != '\n');
        goto request;
    }
    input[strlen(input) - 1] = '\0';

    int i = 0;
    for (; i < strlen(input); ++i) {
        if (input[i] == ' ')
            break;
    }

    memcpy(response->command, input, sizeof(char) * (i));
    response->command[i + 1] = '\0';

    if (i + 1 < strlen(input)) {
        memcpy(response->args, input + i + 1, sizeof(char) * (strlen(input) - i));
        response->args[strlen(input) - i] = '\0';
    }

    printf("\033[0m");
}

void help() {
    printf("Examples of commands:\n");
    printf("0. help\n");
    printf("0. exit\n");
    printf("1. add 12 a\n");
    printf("2. del 12\n");
    printf("3. tr 10 20 - reverse tree traversal in diapason\n");
    printf("4. find 12\n");
    printf("5. sfind - find the most different nodes\n");
    printf("6. file FILENAME\n");
    printf("7. write\n");
    printf("    7.1. write -p  -  will print a pointer to the parent for each node\n");
    printf("8. print\n");
    printf("9. mock\n");

    printf("\nYou can try to enter example command:\n");
    printf("add 15 a\n");
}

