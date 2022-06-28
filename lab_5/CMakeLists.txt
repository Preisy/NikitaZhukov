cmake_minimum_required(VERSION 3.16)
project(lab_5 C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99 -lm")



include_directories(graph)
add_executable(lab_5 main.c graph/Graph.c)
add_executable(test test.c graph/PQueue.c graph/Graph.c)

target_link_libraries(lab_5 m)
target_link_libraries(test m)
