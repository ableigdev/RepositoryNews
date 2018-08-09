cmake_minimum_required(VERSION 3.10)

project(rpnews)
include(${CMAKE_SOURCE_DIR}/cmake/FindGit2.cmake)

add_subdirectory(src)
add_subdirectory(tests)
