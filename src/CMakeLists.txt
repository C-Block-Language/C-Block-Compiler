cmake_minimum_required(VERSION 4.1)
project(C_BLOCK_COMPILER)

set(CMAKE_C_STANDARD 23)

add_executable(C_BLOCK_COMPILER
        main.c
        string_struct.c
        string_struct.h
        file_utils.c
        file_utils.h
        token.c
        token.h
)
