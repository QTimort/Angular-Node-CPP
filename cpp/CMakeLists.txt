cmake_minimum_required(VERSION 3.17)
project(cpp)
project(exec)

set(CMAKE_CXX_STANDARD 20)

add_library(cpp SHARED  library/library.cpp library/library.h executable/main.cpp executable/main.h)
add_executable(exec library/library.cpp library/library.h executable/main.cpp executable/main.h)
