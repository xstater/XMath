cmake_minimum_required(VERSION 3.03)

project(XMathTest)

include_directories(
		./
		./vmath)

add_executable(test1 tests/test1.cpp)