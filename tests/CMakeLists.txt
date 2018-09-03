cmake_minimum_required(VERSION 3.10)

include(${CMAKE_SOURCE_DIR}/cmake/GoogleTest.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/FindGit2.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/FindQt.cmake)

add_subdirectory(CreateNewGitRepository)
