cmake_minimum_required(VERSION 3.16)
project(DemoSyntacore)

set(CMAKE_CXX_STANDARD 20)

add_executable(DemoSyntacore
        inc/structure/BalancedTree.h
        src/main.cpp)
