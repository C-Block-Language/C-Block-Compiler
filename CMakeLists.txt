

cmake_minimum_required(VERSION 4.1)
project(C_BLOCK_COMPILER)



add_executable(C_BLOCK_COMPILER)

set_target_properties(C_BLOCK_COMPILER
        PROPERTIES
        LANGUAGE C
        LINKER_LANGUAGE C
        COMPILE_WARNING_AS_ERROR ON
        C_STANDARD 23
        C_STANDARD_REQUIRED ON
)


target_sources(C_BLOCK_COMPILER PRIVATE

        # Program start
        src/main.c



        # File utils
        src/file/utils.h
        src/file/utils.c



        # String struct
        src/string/struct.h
        src/string/struct/definition.h
        src/string/struct/operations.h
        src/string/struct/operations.c
)


