cmake_minimum_required(VERSION 3.5)
project(adapter_example)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES adaptor.cpp)
add_executable(adapter_example ${SOURCE_FILES})
