cmake_minimum_required(VERSION 3.10)

project(TestHelpers)
getSources(${CMAKE_SOURCE_DIR}/rpnews/* SRC_LIST)

add_executable(TestHelpers ${SRC_LIST} TestHelpers.cpp)

# Target libgit2, qt and gtest libraries
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${LIBGIT2_INCLUDE}>)
target_link_libraries(${PROJECT_NAME} $<BUILD_INTERFACE:${LIBGIT2_LIBRARY}> googletest Qt5::Widgets Qt5::Multimedia) 
