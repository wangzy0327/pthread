cmake_minimum_required(VERSION 3.9)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 17)

project(multi-thread)

add_subdirectory(00_first_thread)
add_subdirectory(01_create_thread)
add_subdirectory(02_exit_thread)
add_subdirectory(03_cancel_thread)

