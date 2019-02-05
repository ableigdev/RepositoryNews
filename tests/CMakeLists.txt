cmake_minimum_required(VERSION 3.10)

include(${CMAKE_SOURCE_DIR}/cmake/FindQt.cmake)
include_directories(${CONAN_INCLUDE_DIRS_GTEST})
include_directories(${CMAKE_SOURCE_DIR}/rpnews)
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/rpnews/*/*.cpp)
file(GLOB HEADERS ${CMAKE_SOURCE_DIR}/rpnews/*/*.h)


add_subdirectory(CreateNewGitRepository)
add_subdirectory(GMockTesting)
add_subdirectory(TestCrypt)
add_subdirectory(TestHelpers)

