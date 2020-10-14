cmake_minimum_required(VERSION 3.5)
project(cpp_1604)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SOURCE_FILES main.cpp)
add_executable(cpp_1604 ${SOURCE_FILES})
