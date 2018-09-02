cmake_minimum_required(VERSION 3.10)

project(Test)

add_executable(Test test.cpp)

target_link_libraries(Test googletest)

