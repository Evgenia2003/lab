cmake_minimum_required(VERSION 3.20)
project(untitled C)

set(CMAKE_C_STANDARD 11)


add_executable(project main.c)
add_executable(untitled main.c
        libs/data_structures/vector/vector.h
        libs/data_structures/vector/vector.c libs/data_structures/matrix/matrix.h libs/data_structures/matrix/matrix.c "libs/data_structures/ string/string_.c"
        "libs/data_structures/ string/string_.h")
add_library(str string/string_.h string/string_.c)
target_link_libraries(project str)