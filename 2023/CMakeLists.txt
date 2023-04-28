cmake_minimum_required(VERSION 3.26)

project(c-learning-2023)

add_subdirectory("./queue")
add_subdirectory("./linked_list")
add_executable(c-learning-2023-find_substring find_substring.c)
