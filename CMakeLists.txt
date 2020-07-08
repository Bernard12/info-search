cmake_minimum_required(VERSION 3.14)
project(info_search)

set(CMAKE_C_FLAGS "${CMAKE_CFLAGS} -O2")

add_executable(
        info_search
        src/main.c
        src/tokenize/Tokenize.c
)
