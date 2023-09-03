cmake_minimum_required(VERSION 3.16)
project(DemoSyntacore)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/inc)

add_executable(DemoSyntacore
        src/main.cpp
        src/console_utils/StringParser.cpp)