cmake_minimum_required(VERSION 3.5)
project(shared_ptr_test)


set(CMAKE_CXX_CFLAGS "${CMAKE_CXX_CFLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)

add_executable(shared_ptr_test ${SOURCE_FILES})
