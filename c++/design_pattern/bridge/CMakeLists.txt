cmake_minimum_required(VERSION 3.5)
project(bridge_example)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES bridge.cpp)
add_executable(bridge_example ${SOURCE_FILES})
