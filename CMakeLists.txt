cmake_minimum_required(VERSION 3.5)
cmake_policy(SET CMP0076 NEW)
project(queens C)
set(CMAKE_C_STANDARD 11)

option(NDEBUG "Disable debugging messages" OFF)
if(NDEBUG)
    add_compile_options(-DNDEBUG)
endif(NDEBUG)

add_subdirectory(src)
