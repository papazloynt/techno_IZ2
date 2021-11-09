cmake_minimum_required(VERSION 3.20)
project(IZ2)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-g -O0 -Wall -W -fprofile-arcs -ftest-coverage -Werror -Wpedantic")

option(IS_SEQUENTIAL "Use sequential library" ON)

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

target_link_libraries(sequential
        common)

# Parallel
add_library(parallel SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/src/parallel_search.c)

target_include_directories(parallel PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(parallel
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

# Enable tests
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third_party/googletest)
enable_testing()

# Tests common functions
add_executable(common_tests tests/common_tests.cpp)

target_include_directories(common_tests PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(common_tests
        gtest_main
        common)

# Tests sequential functions
add_executable(sequential_tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/sequential_tests.cpp)

target_include_directories(sequential_tests PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(sequential_tests
        gtest_main
        sequential)

# Tests sequential functions
add_executable(parallel_tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/parallel_tests.cpp)

target_include_directories(parallel_tests PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(parallel_tests
        gtest_main
        parallel)