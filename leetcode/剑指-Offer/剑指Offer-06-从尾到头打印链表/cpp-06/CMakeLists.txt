cmake_minimum_required(VERSION 3.5)
project(cpp_06)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SOURCE_FILES main.cpp)
add_executable(cpp_06 ${SOURCE_FILES})
