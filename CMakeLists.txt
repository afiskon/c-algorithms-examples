cmake_minimum_required(VERSION 2.8)

project(c-algorithms-examples)

add_subdirectory(deps/algorithms)

add_executable(slist_example slist_example.c)
target_link_libraries(slist_example CAlgorithms)
