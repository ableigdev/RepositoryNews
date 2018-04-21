cmake_minimum_required(VERSION 2.8)

project(rpnews_tests)

include_directories(../src)

set(GTEST_SRC ../googletest/googletest/src/gtest-all.cc)
include_directories(../googletest/googletest ../googletest/googletest/include)

add_library(googletest STATIC ${GTEST_SRC})
target_link_libraries(googletest ${CMAKE_THREAD_LIBS_INIT})

add_executable(rpnews_tests rpnews_tests.cpp)
target_link_libraries(rpnews_tests googletest)