cmake_minimum_required(VERSION 3.16.3)
project(lab_2 C)

set(CMAKE_C_STANDARD 99)

include_directories(src)
include_directories(lib)

add_executable(lab_2 main.c src/RoundRobin.c lib/QueueVector.c lib/Pair.c)
