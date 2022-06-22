#ifndef LAB4_GRAPHGENERATOR_H
#define LAB4_GRAPHGENERATOR_H

#include "../../tree/BinaryTree.h"

typedef enum DrawMode {
    DEFAULT,
    PARENT,
} DrawMode;

int createPngGraph(const BinaryTree *tree, DrawMode mode);

#endif
