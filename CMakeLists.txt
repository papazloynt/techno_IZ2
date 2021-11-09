cmake_minimum_required(VERSION 3.20)
project(IZ2 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-g -O0 -Wall -W -fprofile-arcs -ftest-coverage -Werror -Wpedantic")

option(IS_SEQUENTIAL "Use sequential library" OFF)

# Common lib
add_library(common STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/common.c)

target_include_directories(common PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include)
# Sequential
add_library(sequential STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sequential_search.c)

target_include_directories(sequential PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(sequential PUBLIC
        common)

# Parallel
add_library(parallel SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/src/parallel_search.c)

target_include_directories(parallel PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(parallel PUBLIC
        common)

# Main
add_executable(main src/main.c)

target_include_directories(main PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(IS_SEQUENTIAL)
    target_link_libraries(main PUBLIC
            sequential)
else()
    target_link_libraries(main PUBLIC
            parallel)
endif()

# Tests