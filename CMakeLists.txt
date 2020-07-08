cmake_minimum_required(VERSION 3.14)
project(info_search)

#set(CMAKE_C_FLAGS "${CMAKE_CFLAGS} -O3 -march=native")
#set(CMAKE_CXX_FLAGS "${CMAKE_CFLAGS} -O3 -march=native")

add_executable(
        info_search
        src/main.c
        src/tokenize/Tokenize.c
)
