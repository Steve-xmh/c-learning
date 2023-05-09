cmake_minimum_required(VERSION 3.26)

project(c-learning-2023)

add_executable(c-learning-2023-huffmantree main.c vector.c)

if(MSVC)
    target_compile_options(c-learning-2023-huffmantree PRIVATE /W4 /WX)
else()
    target_compile_options(c-learning-2023-huffmantree PRIVATE -Wall -Wextra -pedantic)
endif()
