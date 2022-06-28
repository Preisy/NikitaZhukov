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
    printf("1. addv 1 2\n");
    printf("2. adde 1 2 3 4\n");
    printf("3. delv 1 2\n");
    printf("4. dele 1 2 3 4\n");
    printf("5. find 1 2 3 4\n");
    printf("6. sfind 1 2 3 4\n");
    printf("7. print\n");

    printf("\nYou can try to enter example command:\n");
    printf("adde 1 2 3 4\n");
}

