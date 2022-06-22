cmake_minimum_required(VERSION 3.16)
project(lab_4a C)


set(CMAKE_C_FLAGS "-lreadline")

include_directories(model/tree/binary)
include_directories(tree/graph)
include_directories(controller/dialog)
include_directories(view)

add_executable(lab_4a main.c
        tree/Tree.c
        tree/Node.c
        tree/Graph.c
        tree/Graph.c
        controller/TreeController.c view/Dialog.c view/Dialog.h)
