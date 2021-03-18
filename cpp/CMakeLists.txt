cmake_minimum_required(VERSION 3.17)
project(library)
project(executable)

set(CMAKE_CXX_STANDARD 20)

add_library(library SHARED library/entry_point.cpp library/entry_point.h)
add_executable(executable executable/main.cpp executable/main.h)