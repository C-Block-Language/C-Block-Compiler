

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



        # Log signal
        src/log_signal.h



        # File utils
        src/file/utils.h
        src/file/utils.c



        # String struct
        src/string/struct.h
        src/string/struct/definition.h
        src/string/struct/operations.h
        src/string/struct/operations.c



        # String pointer
        src/string/pointer.h
        src/string/pointer/definition.h
        src/string/pointer/operations.h
        src/string/pointer/operations.c



        # Token struct
        src/token/struct.h
        src/token/struct/definition.h
        src/token/struct/operations.h
        src/token/struct/operations.c



        # Token stream
        src/token/stream.h
        src/token/stream/definition.h
        src/token/stream/operations.h
        src/token/stream/operations.c



        # Token Finite State Machine
        src/token/fms.h
        src/token/fms.c
)


