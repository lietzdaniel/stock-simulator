cmake_minimum_required(VERSION 3.20.0)
project(TQueue)

add_library(TQueue INTERFACE)
target_include_directories(TQueue INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
