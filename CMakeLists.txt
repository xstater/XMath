cmake_minimum_required(VERSION 3.12)
project(XMath)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(test2
        Matrix.h
        Tools.h
        Vector.h

        test2.cpp)
