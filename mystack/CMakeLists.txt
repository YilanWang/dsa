cmake_minimum_required(VERSION 3.8)
project(mystack)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp STACK.h stackuse.cpp use.h)
add_executable(mystack ${SOURCE_FILES})