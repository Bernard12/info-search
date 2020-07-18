cmake_minimum_required(VERSION 3.14)
project(info_search)


#set(CMAKE_C_FLAGS "${CMAKE_CFLAGS} -O0 -march=native")
#set(CMAKE_CXX_FLAGS "${CMAKE_CFLAGS} -O0 -pg")
set(CMAKE_CXX_FLAGS "${CMAKE_CFLAGS} -O3 -march=native")

add_executable(
        info_search
        src/main.cpp
        src/tokenize/Tokenize.cpp
        src/common/hash/hash.cpp
        src/common/common.h
        src/boolean/index.cpp
        src/common/vector/IntVector.cpp
        src/expr_parser/parser.cpp
)

