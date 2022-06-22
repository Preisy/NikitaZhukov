#include <stdlib.h>
#include <time.h>
#include "Dialog.h"
#include "string.h"

char* getString(char* str) {
    char* res = (char*) malloc(sizeof (char) * (strlen(str) + 1));
    memcpy(res, str, sizeof(char) * strlen(str));
    res[strlen(str)] = '\0';
    return res;
}

int main() {
//    BinaryTree *tree = getBinaryTree();
    BinaryTree *tree = getBinaryTreeFromFile("/mnt/d/C/2sem_aisd/NikitaZukov/lab_4a/input.txt");

//    addBT(tree, 10, getString("a"));
//    addBT(tree, 5, getString("b"));
//    addBT(tree, 15, getString("c"));
//    addBT(tree, 17, getString("d"));
//    addBT(tree, 12, getString("e"));
//    addBT(tree, 11, getString("e"));
//    addBT(tree, 12, getString("f"));

//    deleteBT(tree, 11);
//    deleteBT(tree, 10);

    writeNLR_BT(tree, DEFAULT);
    destroyBinaryTreeDeep(tree);
    return 0;
}

//int main() {
//    const char *messages[] = {"0. Quit", "1. Add", "2. Find", "3. Delete", "4. Show", "5. Mock data", "6. Get tree from file"};
//    const int messageSize = sizeof(messages) / sizeof(messages[0]);
//    int (*functions[])(BinaryTree *) = {NULL, D_AddBT, D_FindBT, D_DeleteBT, D_ShowBT, D_MockBT};
//    BinaryTree *tree = getBinaryTree();
//    int actionIndex;
//    while ((actionIndex = dialog(messages, messageSize))) {
//        if (actionIndex == 6) {
//            if (!D_GetFromFile(&tree)) break;
//        } else if (!functions[actionIndex](tree)) break;
//    }
//    puts("That's all. Bye!\n");
//    destroyBinaryTreeDeep(tree);
//    return 0;
//}