cmake_minimum_required(VERSION 3.16)
project(DemoSyntacore)

set(CMAKE_CXX_STANDARD 20)

include_directories(inc)
include_directories(inc/structure)

add_executable(DemoSyntacore
        src/main.cpp)
