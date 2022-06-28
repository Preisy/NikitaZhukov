cmake_minimum_required(VERSION 3.16)
project(lab_5 C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99 -lm")



include_directories(graph)
include_directories(controller)
include_directories(view)
add_executable(lab_5 main.c graph/Graph.c graph/PQueue.c controller/GraphController.c view/Dialog.c)

target_link_libraries(lab_5 m)
