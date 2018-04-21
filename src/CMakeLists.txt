cmake_minimum_required(VERSION 3.10)

project(rpnews)

add_executable(rpnews main.cpp)

message(STATUS "${CMAKE_CURRENT_BINARY_DIR}")
target_include_directories(rpnews PUBLIC ../libgit2/include)
target_link_libraries(rpnews ../../libgit2/build/Debug/git2)