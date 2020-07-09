cmake_minimum_required(VERSION 3.14)
project(info_search)


set(CMAKE_C_FLAGS "${CMAKE_CFLAGS} -O3 -march=native")

add_executable(
        info_search
        src/main.cpp
        src/tokenize/Tokenize.cpp
        src/common/common.h)

