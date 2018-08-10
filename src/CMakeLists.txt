cmake_minimum_required(VERSION 3.10)

project(rpnews)

include(${CMAKE_SOURCE_DIR}/cmake/FindGit2.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/FindQt.cmake)

# Populate a CMake variable with the sources
set(helloworld_SRCS
        mainwindow.ui
        mainwindow.cpp
        main.cpp
        )
# Tell CMake to create the helloworld executable
add_executable(rpnews ${helloworld_SRCS})
# Use the Widgets module from Qt 5
target_link_libraries(rpnews Qt5::Widgets)

#add_executable(rpnews main.cpp)

target_include_directories(rpnews PUBLIC ${LIBGIT2_INCLUDE})
target_link_libraries(rpnews ${LIBGIT2_LIBRARY})