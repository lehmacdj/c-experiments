cmake_minimum_required(VERSION 3.6)
project(Accounts)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Werror")

set(SOURCE_FILES bst.c test_bst.c)
add_executable(test_bst ${SOURCE_FILES})
