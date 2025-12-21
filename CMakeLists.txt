cmake_minimum_required(VERSION 3.15)
project(ialloc C)
add_library(ialloc STATIC ialloc.c)
target_include_directories(ialloc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
