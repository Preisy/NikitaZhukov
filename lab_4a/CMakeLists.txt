cmake_minimum_required(VERSION 3.16)
project(lab_4a C)


set(CMAKE_C_FLAGS "-lreadline")

include_directories(model/tree/binary)
include_directories(controller/graph)
include_directories(controller/dialog)

add_executable(lab_4a main.c
        tree/BinaryTree.c
        tree/BNode.c
        controller/graph/GraphGenerator.c
        controller/graph/GraphGenerator.c
        controller/dialog/Dialog.c)
