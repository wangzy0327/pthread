add_executable(16_cpp_condition_thread thread.cpp)
set(CMAKE_CXX_STANDARD 11)
# add_compile_options("-std=c++11")
target_link_libraries(16_cpp_condition_thread PRIVATE pthread)

