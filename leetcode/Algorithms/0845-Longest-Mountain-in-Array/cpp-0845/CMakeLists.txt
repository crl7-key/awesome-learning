cmake_minimum_required(VERSION 3.5)
project(cpp-0845)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SOURCE_FILES main.cpp)

add_executable(cpp-0845 ${SOURCE_FILES})