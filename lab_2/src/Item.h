#ifndef LAB_2_ITEM_H
#define LAB_2_ITEM_H

#include "stdlib.h"

typedef struct Item {
    char* id;
    int ta;
    int ts;
} Item;

void deleteItem(Item* this);

#endif //LAB_2_ITEM_H
