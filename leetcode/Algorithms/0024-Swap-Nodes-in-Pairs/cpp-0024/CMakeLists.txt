cmake_minimum_required(VERSION 3.5)
project(cpp-0024)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SOURCE_FILES main.cpp)
add_executable(cpp-0024 ${SOURCE_FILES})
