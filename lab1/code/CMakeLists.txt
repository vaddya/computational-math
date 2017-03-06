cmake_minimum_required(VERSION 3.6)
project(lab1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp lagrange.h lagrange.cpp quanc8.h quanc8.cpp splines.h splines.cpp main.h)
add_executable(code ${SOURCE_FILES})