cmake_minimum_required(VERSION 3.16)
project("AMSTL")

set(CMAKE_CXX_STANDARD 14)

add_library(AMSTL src/ArrayList.cpp)

target_include_directories(AMSTL PUBLIC include)