cmake_minimum_required(VERSION 3.26)

project(c-learning-2023)

add_executable(c-learning-2023-huffmantree-2 main.c)

if(MSVC)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    target_compile_options(c-learning-2023-huffmantree-2 PRIVATE /W4 /WX /D_CRT_SECURE_NO_WARNINGS)
else()
    target_compile_options(c-learning-2023-huffmantree-2 PRIVATE -Wall -Wextra -pedantic)
endif()
