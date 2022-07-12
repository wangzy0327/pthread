add_executable(15_cpp_mutex_thread thread.cpp)
set(CMAKE_CXX_STANDARD 11)
# add_compile_options("-std=c++11")
target_link_libraries(15_cpp_mutex_thread PRIVATE pthread)

