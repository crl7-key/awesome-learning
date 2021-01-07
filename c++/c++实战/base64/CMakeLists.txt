cmake_minimum_required(VERSION 3.5)
project(base64_test)


set(CMAKE_CXX_CFLAGS "${CMAKE_CXX_CFLAGS} -std=c++17")

set(SOURCE_FILES main.cpp base64.cpp)

add_executable(base64_test ${SOURCE_FILES})
