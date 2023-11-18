cmake_minimum_required(VERSION 3.20)

project("Stock Simulator")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(UTILS_SOURCES
    utils/tqueue/tqueue.cpp
)
add_library(TQueue ${UTILS_SOURCES})
add_executable(Main main.cpp)

target_include_directories(TQueue PUBLIC utils)
target_link_libraries(Main PRIVATE TQueue)

