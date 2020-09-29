cmake_minimum_required(VERSION 3.5)
project(cpp-0145)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SOURCE_FILES main.cpp)

add_executable(cpp-0145 ${SOURCE_FILES})