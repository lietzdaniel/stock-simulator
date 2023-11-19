cmake_minimum_required(VERSION 3.20)
include(FetchContent)
project("Stock Feed Simulator")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.11.0
)

FetchContent_MakeAvailable(googletest)


add_executable(Stock_Feed stock_feed.h stock_feed.cpp)
