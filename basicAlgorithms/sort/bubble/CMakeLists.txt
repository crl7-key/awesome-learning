cmake_minimum_required(VERSION 3.5)
project(bubble_sort)

set(CMAKE_CXX_CFLAGS "{CMAKE_CXX_CFLAGS} -std=c++17")

aux_source_directory(. DIR_SRCS)

add_executable(bubble_sort ${DIR_SRCS})