cmake_minimum_required(VERSION 3.03)

project(XMathTest)

include_directories(
		./
		./vmath)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 ")

add_executable(test1 tests/test1.cpp vmath/vmath.cpp)