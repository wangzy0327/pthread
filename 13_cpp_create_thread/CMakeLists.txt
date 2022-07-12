add_executable(13_cpp_create_thread thread.cpp)
set(CMAKE_CXX_STANDARD 11)
# add_compile_options("-std=c++11")
target_link_libraries(13_cpp_create_thread PRIVATE pthread)

