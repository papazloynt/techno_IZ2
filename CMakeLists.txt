cmake_minimum_required(VERSION 3.20)
project(IZ2 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Werror -Wpedantic")

# Sequential
add_library(sequential STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sequential_search.c)

target_include_directories(sequential PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Parallel
add_library(parallel SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/src/parallel_search.c)

target_include_directories(parallel PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include)













# Not Good

add_executable(main_seq src/main.c)

target_link_libraries(main_seq PUBLIC
        sequential)

target_include_directories(main_seq PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)