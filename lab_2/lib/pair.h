#ifndef LAB_2_PAIR_H
#define LAB_2_PAIR_H

#include "stdlib.h"

typedef struct Pair {
    char* id;
    int ts;
} Pair;

Pair getPair(char* x, int y);



#endif //LAB_2_PAIR_H
