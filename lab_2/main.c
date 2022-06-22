#include <stdio.h>
#include "stdlib.h"
#include <string.h>

#include "RoundRobin.h"

int validate(char sym) {
    if ('0' <= sym && sym <= '9')
        return 1;
    else
        return 0;
}

int convertToInt(char* begin, char* end) {
    int res = 0;
    for (; begin != end; ++begin) {
        if (validate(*begin))
            res = res * 10 + (*begin - '0');
        else
            return -1;
    }

    return res;
}


int main() {
    while(1) {
        request:
        printf("\033[34m>>> \033[36m");

        char input[256];
        size_t inputLen;
        if (fgets(input, sizeof(input), stdin) == NULL || strlen(input) == 1) {
            printf("\033[0m");
            printf("Too big string. Try again\n");
            goto request;
        }
        inputLen = strlen(input);
        input[inputLen - 1] = '\0';
        printf("\033[0m");

        if (strcmp(input, "exit") == 0) {
            break;
        }

        int i = 0;
        int threadsAmount;
        for (; i < strlen(input); ++i) {
            if (!validate(input[i])) {
                threadsAmount = convertToInt(input, input + i);
                break;
            }
        }
        if (threadsAmount <= 0) {
            printf("Incorrect input. Try again\n");
            goto request;
        }
        if (input[i] != ' ') {
            printf("Incorrect input. Try again\n");
            goto request;
        }
        ++i;

        int bufLength = 10;
        int len = 0;
        Item* items = (Item*) calloc(bufLength, sizeof(Item));

        for (; i < strlen(input);) {
            char* id;
            int j = i;
            for (; j < strlen(input); ++j) {
                if (input[j] == '/') {
                    id = (char*) calloc(j - i + 1, sizeof(char));
                    strncpy(id, input + i, sizeof (char) * (j - i));
                    id[j - i] = '\0';
                    break;
                }
            }
            if (strcmp(id, "") == 0) {
                free(id);
                printf("Incorrect input. Try again\n");
                for (int j = 0; j < len; ++j) free(items[j].id);
                free(items);
                goto request;
            }

            int ta = -1;
            i = ++j;
            for (; j < strlen(input); ++j) {
                if (input[j] == '/') {
                    ta = convertToInt(input + i, input + j);
                    break;
                }
            }
            if (ta <= 0) {
                free(id);
                printf("Incorrect input. Try again\n");
                for (int j = 0; j < len; ++j) free(items[j].id);
                free(items);
                goto request;
            }

            int ts = -1;
            i = ++j;
            for (; j < strlen(input); ++j) {
                if (input[j] == ' ') {
                    ts = convertToInt(input + i, input + j);
                    break;
                } else if (j == strlen(input) - 1) {
                    ts = convertToInt(input + i, input + j + 1);
                    break;
                }
            }
            if (ts <= 0) {
                free(id);
                printf("Incorrect input. Try again\n");
                for (int j = 0; j < len; ++j) free(items[j].id);
                free(items);
                goto request;
            }

            i = j + 1;


            if (bufLength <= len) {
                bufLength *= 2;
                Item* buf = (Item*) malloc(sizeof(Item) * bufLength);
                memcpy(buf, items, sizeof (Item) * (len));
                free(items);
                items = buf;
            }
            Item buf = {id, ta, ts};
            if (len != 0 && buf.ta < items[len - 1].ta) {
                free(id);
                printf("Incorrect input. Try again\n");
                for (int j = 0; j < len; ++j) free(items[j].id);
                free(items);
                goto request;
            }

            items[len] = buf;
            ++len;
        }


        distributeProcesses( 2, items, len);

        for (int j = 0; j < len; ++j) free(items[j].id);
        free(items);
    }


    return 0;
}

//2 a/1/20 b/1/15 c/2/10 d/5/8 e/6/5 f/6/9 a/7/20 b/8/15 c/9/10 d/10/8 e/11/5 f/12/9

//Item items[] = {{"a", 1, 5},
//                    {"b", 1, 3},
//                    {"c", 2, 10},
//                    {"d", 5, 8},
//                    {"e", 6, 5},
//                    {"f", 25, 9}};