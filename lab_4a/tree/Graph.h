#ifndef LAB4_GRAPHGENERATOR_H
#define LAB4_GRAPHGENERATOR_H

#include "Tree.h"

typedef enum DrawMode {
    Default,
    Parent,
} DrawMode;

int createGraph(Tree *tree, DrawMode mode);

#endif
