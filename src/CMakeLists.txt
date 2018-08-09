cmake_minimum_required(VERSION 3.10)

project(rpnews)

add_executable(rpnews main.cpp)

target_include_directories(rpnews PUBLIC ${LIBGIT2_INCLUDE})
target_link_libraries(rpnews ${LIBGIT2_LIBRARY})