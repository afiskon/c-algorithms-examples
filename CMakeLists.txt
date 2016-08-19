cmake_minimum_required(VERSION 2.8)

project(c-algorithms-examples)

include_directories(deps/algorithms/include)
add_subdirectory(deps/algorithms/src)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g")

add_executable(rbtree_example rbtree_example.c)
target_link_libraries(rbtree_example CAlgorithms)
