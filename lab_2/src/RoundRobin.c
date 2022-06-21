#include "RoundRobin.h"
#include "lib.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

int getNumSize(int num) {
    int size = 0;
    while (num) {
        num /= 10;
        ++size;
    }
    return size;
}

void intToString(int value, char* buffer) {
    int n = value > 0 ? value : -value;
    int size = getNumSize(n);
    if (value < 0) size += 1;

    buffer += size + 1;
    *--buffer = 0;
    do {
        *--buffer = n % 10 + '0';
        n /= 10;
    } while (n != 0);

    if (value < 0)
        *--buffer = '-';
}


char* createSpace(int len) {
    char* res = (char*) malloc(sizeof(char) * (len + 1));
    for (int i = 0; i < len; ++i) {
        res[i] = ' ';
    }
    res[len] = '\0';
    return res;
}


char* concat(char **s1, char *s2) {

    size_t len1 = strlen(*s1);
    size_t len2 = strlen(s2);

    char *result = malloc(len1 + len2 + 1);

    if (!result) {
        fprintf(stderr, "malloc() failed: insufficient memory!\n");
        return NULL;
    }

    memcpy(result, *s1, len1);
    memcpy(result + len1, s2, len2 + 1);
    free(*s1);
    *s1 = result;

    return result;
}

void appendStateToHistory(char** history, Queue** threads, int threadsAmount, int currentTime) {
    char** strings = (char**) malloc (sizeof(char*) * threadsAmount);
    int maxSize = getNumSize(currentTime);
    for (int i = 0; i < threadsAmount; ++i) {
        strings[i] = toStringQueue(threads[i]);
        maxSize = maxSize >= (int) strlen(strings[i])
                ? maxSize :
                (int) strlen(strings[i]);
    }
    char str[11];
    intToString(currentTime, str);
    char* spaces = createSpace(maxSize - (int) strlen(str) + 2);
    concat(&history[0], str);
    concat(&history[0], spaces);
    free(spaces);

    for (int i = 1; i < threadsAmount + 1; ++i) {
        spaces = createSpace(maxSize - (int) strlen(strings[i - 1]) + 2);
        concat(&history[i], strings[i - 1]);
        concat(&history[i], spaces);
        free(spaces);
    }

    for (int i = 0; i < threadsAmount; ++i) free(strings[i]);
    free(strings);
}

int distributeProcesses(int threadsAmount, Item* inp, int n) {
    char** history = (char**) malloc(sizeof(char*) * (threadsAmount + 1));
    for (int i = 0; i < threadsAmount + 1; ++i) {
        history[i] = (char*) malloc(sizeof(char));
        history[i][0] = '\0';
    }


    Queue** threads = (Queue**) malloc(sizeof (Queue*) * threadsAmount);
    for (int i = 0; i < threadsAmount; ++i)
        threads[i] = getQueue();

    int threadsIt = 0;
    for (int currentTime = 0, i = 0; 1; ++currentTime) {
        int printFlag = 0;
        while (i < n && currentTime == inp[i].ta) {
            printFlag = 1;
            Pair p = {inp[i].id, inp[i].ts};
            pushQueue(threads[threadsIt], p);
            threadsIt = (threadsIt + 1) % threadsAmount;
            ++i;
        }

        int countNulls = 0;
        for (int j = 0; j < threadsAmount; ++j) {
            Pair* el = topQueue(threads[j]);
            if (el == NULL) {
                ++countNulls;
                continue;
            };
            --el->ts;
            if (el->ts == 0) {
                popQueue(threads[j]);
                printFlag = 1;
            }
        } // сделать выход из цикла здесь как обработаются все процессы

        if (countNulls == threadsAmount && i >= n)
            break;

        if (printFlag == 1) {
            appendStateToHistory(history, threads, threadsAmount, currentTime);
        }
    }

    for (int i = 0; i < threadsAmount + 1; ++i) {
        if (i == 0) {
            printf("   %s\n", history[i]);
        } else {
            printf("%d: %s\n", i, history[i]);
        }
    }

    for (int i = 0; i < threadsAmount; ++i) deleteQueue(threads[i]);
    free(threads);

    for (int i = 0; i < threadsAmount + 1; ++i) free(history[i]);
    free(history);

    return 1;
}


