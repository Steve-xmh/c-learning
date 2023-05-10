cmake_minimum_required(VERSION 3.26)

project(c-learning-2023)

if(MSVC)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()

add_executable(c-learning-2023-linked-list-test1 test1.c)
add_executable(c-learning-2023-linked-list-test2 test2.c)
add_executable(c-learning-2023-linked-list-test3 test3.c)
add_executable(c-learning-2023-linked-list-test4 test4.c)
add_executable(c-learning-2023-linked-list-test5 test5.c)
add_executable(c-learning-2023-linked-list-test6 test6.c)
