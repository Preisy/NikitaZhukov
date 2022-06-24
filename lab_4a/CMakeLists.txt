cmake_minimum_required(VERSION 3.16)
project(lab_4a C)


include_directories(model/tree/binary)
include_directories(tree)
include_directories(controller/dialog)
include_directories(view)

add_executable(lab_4a main.c
        tree/Tree.c
        tree/Node.c
        controller/TreeController.c
        view/Dialog.c)
