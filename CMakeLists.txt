cmake_minimum_required(VERSION 2.8)

project(c-algorithms-examples)

add_subdirectory(deps/algorithms)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")

add_executable(slist_example slist_example.c)
target_link_libraries(slist_example CAlgorithms)

add_executable(dlist_example dlist_example.c)
target_link_libraries(dlist_example CAlgorithms)

add_executable(rbtree_example rbtree_example.c)
target_link_libraries(rbtree_example CAlgorithms)

add_executable(htable_example htable_example.c)
target_link_libraries(htable_example CAlgorithms)
