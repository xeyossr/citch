cmake_minimum_required(VERSION 3.10)
project(Citch LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -flto -funroll-loops -ffast-math -ftree-vectorize")
endif()

set(SOURCE_FILE citch.cpp)

add_executable(citch ${SOURCE_FILE})
