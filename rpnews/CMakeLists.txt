cmake_minimum_required(VERSION 3.10)

# Set SOURCES variable
file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*/*.cpp)
set(mainFile main.cpp)

# Set HEADERS variable
file(GLOB HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h ${CMAKE_CURRENT_SOURCE_DIR}/*/*.h)

# Set UIS variable
file(GLOB UIS ${CMAKE_CURRENT_SOURCE_DIR}/*/*.ui)

#Set RCS variable
file(GLOB RCS ${CMAKE_CURRENT_SOURCE_DIR}/*/*.qrc)

include(${CMAKE_SOURCE_DIR}/cmake/ProjectConfig.cmake)
