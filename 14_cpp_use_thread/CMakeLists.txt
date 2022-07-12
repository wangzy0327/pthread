add_executable(14_cpp_use_thread thread.cpp)
set(CMAKE_CXX_STANDARD 11)
# add_compile_options("-std=c++11")
target_link_libraries(14_cpp_use_thread PRIVATE pthread)

