cmake_minimum_required(VERSION 3.26)

project(c-learning-2023)

add_executable(c-learning-2023-bintree main.c)
add_executable(c-learning-2023-bintree-single single.c)

if(MSVC)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    target_compile_options(c-learning-2023-bintree PRIVATE /W4 /WX /D_CRT_SECURE_NO_WARNINGS)
    target_compile_options(c-learning-2023-bintree-single PRIVATE /W4 /WX /D_CRT_SECURE_NO_WARNINGS)
else()
    target_compile_options(c-learning-2023-bintree PRIVATE -Wall -Wextra -pedantic)
    target_compile_options(c-learning-2023-bintree-single PRIVATE -Wall -Wextra -pedantic)
endif()
