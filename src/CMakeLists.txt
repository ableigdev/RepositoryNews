cmake_minimum_required(VERSION 2.8)

project(rpnews)

find_package(libgit2 REQUIRED)
include_directories(${LIBGIT2_INCLUDE_DIR})

add_executable(rpnews main.cpp)
