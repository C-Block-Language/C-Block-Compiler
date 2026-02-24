

cmake_minimum_required(VERSION 4.1)

project("C-Block Compiler" LANGUAGES C)


add_library(compiler_core

        # Log signal
        include/c_block/log_signal.h

        # Pack Build parser
        src/pack_build_parser.c
        include/c_block/pack_build_parser.h


        # File
        include/c_block/file.h
        include/c_block/file/utils.h
        include/c_block/file/id_definition.h
        include/c_block/file/allocator_definition.h
        include/c_block/file/allocator_operations.h
        src/file/allocator_operations.c

        # Implementation specific wrapper headers
        include/c_block/file/sys_ops.h


        # File struct
        include/c_block/file/struct/definition.h
        include/c_block/file/struct/struct_operations.h
        src/file/struct_operations.c



        # String struct
        include/c_block/string/struct.h
        include/c_block/string/ptr_definition.h
        include/c_block/string/struct_operations.h
        src/string/struct_operations.c



        # String pointer
        include/c_block/string/pointer.h
        include/c_block/string/struct_definition.h
        include/c_block/string/ptr_operations.h
        src/string/ptr_operations.c



        # Token struct
        include/c_block/token/struct.h
        include/c_block/token/struct_definition.h
        include/c_block/token/struct_operations.h
        src/token/struct_operations.c



        # Token stream
        include/c_block/token/stream.h
        include/c_block/token/stream/struct_definition.h
        include/c_block/token/stream/struct_operations.h
        src/token/stream/struct_operations.c



        # Token Finite State Machine
        include/c_block/token/automata.h
        src/token/automata.c



        # Token stream pointer
        include/c_block/token/stream_pointer.h
        include/c_block/token/stream/ptr_definition.h
        include/c_block/token/stream/ptr_operations.h
        src/token/stream/ptr_operations.c
        include/c_block/file/struct.h

)



add_executable(win32_build

        # Program start
        src/main.c


)



add_executable(unix_build

        # Program start
        src/main.c

        # system specific operation implementations
        src/file/sys_ops/unix.c

)






set_target_properties(
        compiler_core
        unix_build
        win32_build

        PROPERTIES
        LANGUAGE C
        LINKER_LANGUAGE C
        COMPILE_WARNING_AS_ERROR ON
        C_STANDARD 23
        C_STANDARD_REQUIRED ON
)

include_directories(include)

target_link_libraries(      unix_build      PUBLIC compiler_core    )
target_link_libraries(      win32_build     PUBLIC compiler_core    )

