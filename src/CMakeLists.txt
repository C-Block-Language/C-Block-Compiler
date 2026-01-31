cmake_minimum_required(VERSION 4.1)
project(C_BLOCK_COMPILER)

set(CMAKE_CXX_STANDARD 23)

add_executable(C_BLOCK_COMPILER main.cpp
        token.cpp
        token.h
        c_stream.cpp
        c_stream.h
        parser/parser.cpp
        parser/parser.h
        parser/syntax_structure.cpp
        parser/syntax_structure.h
        parser/substructure/score_holder.cpp
        parser/substructure/score_source.cpp
        parser/substructure/objective_id.cpp
)
