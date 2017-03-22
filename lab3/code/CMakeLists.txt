cmake_minimum_required(VERSION 3.6)
project(lab3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.h main.cpp rkf45.h rkf45.cpp impeuler.h impeuler.cpp)
add_executable(code ${SOURCE_FILES})