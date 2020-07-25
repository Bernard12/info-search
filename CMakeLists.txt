cmake_minimum_required(VERSION 3.14)
project(info_search)


#set(CMAKE_C_FLAGS "${CMAKE_CFLAGS} -O0 -march=native")
#set(CMAKE_CXX_FLAGS "${CMAKE_CFLAGS} -O0 -pg")
#set(CMAKE_CXX_FLAGS "${CMAKE_CFLAGS} -O3 -march=native")
set(CMAKE_CXX_FLAGS "${CMAKE_CFLAGS} -Wall")
#set(CMAKE_CXX_FLAGS "${CMAKE_CFLAGS} -Wall -fsanitize=address")


add_executable(
        info_search
        src/main.cpp
        src/tokenize/Tokenize.cpp
        src/common/hash/hash.cpp
        src/common/common.h
        src/boolean/index.cpp
        src/common/vector/int/IntVector.cpp
        src/common/vector/wstr/WStrVector.cpp
        src/expr_parser/parser.cpp
        src/common/vector/node/WNodeVector.cpp
        src/common/hash-index/hash-index.cpp
        src/common/vector/utils/utils.cpp
        src/boolean/query.cpp
        src/common/forward-index/forward-index.cpp
)

