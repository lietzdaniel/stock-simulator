cmake_minimum_required(VERSION 3.20)
include(FetchContent)
project("Stock Simulator")

add_subdirectory(utils/tqueue)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.11.0
)

FetchContent_MakeAvailable(googletest)

set(TQUEUE_TEST
    tests/tqueue_general_tests.cpp
)

add_executable(TQueue_test ${TQUEUE_TEST})
target_link_libraries(TQueue_test PRIVATE gtest gtest_main TQueue)

set(MAIN_PATH
    src/main.cpp
)

set(MAIN_INCLUDE
    src
)

add_executable(Main ${MAIN_PATH})
target_link_libraries(Main TQueue)
