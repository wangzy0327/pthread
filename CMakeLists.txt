cmake_minimum_required(VERSION 3.9)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 17)

project(multi-thread)

add_subdirectory(00_first_thread)
add_subdirectory(01_create_thread)
add_subdirectory(02_exit_thread)
add_subdirectory(03_cancel_thread)
add_subdirectory(04_ret_thread)
add_subdirectory(05_trick_cancel_thread)
add_subdirectory(06_sync_thread)
add_subdirectory(07_mutex_thread)
add_subdirectory(08_semaphore_thread)
add_subdirectory(09_condition_thread)
add_subdirectory(10_read_write_lock_thread)

