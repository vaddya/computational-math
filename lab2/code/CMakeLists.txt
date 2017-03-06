cmake_minimum_required(VERSION 3.6)
project(lab2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp matrix_lib.cpp matrix.h matrix_lib.h main.h)
add_executable(code ${SOURCE_FILES})