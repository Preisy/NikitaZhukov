#include <stdio.h>

#include "lib.h"
#include "RoundRobin.h"
#include "string.h"


int main() {
    Item items[] = {{"a", 1, 5},
                    {"b", 1, 3},
                    {"c", 2, 10},
                    {"d", 5, 8},
                    {"e", 6, 5},
                    {"f", 25, 9}};

    distributeProcesses( 2, items, sizeof (items) / sizeof (items[0]));

    return 0;
}
