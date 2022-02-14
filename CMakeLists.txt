cmake_minimum_required(VERSION 3.20)
project(untitled C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled main.c
        libs/data_structures/vector/vector.h
        libs/data_structures/vector/vector.c libs/data_structures/matrix/matrix.h libs/data_structures/matrix/matrix.c)
