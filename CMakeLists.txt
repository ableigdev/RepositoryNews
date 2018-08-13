cmake_minimum_required(VERSION 3.10)

project(rpnews)

# Set variables
include(${CMAKE_SOURCE_DIR}/cmake/SetEnv.cmake)

add_subdirectory(${PROJECT_FOLDER})
add_subdirectory(tests)

# Install targets
include(${CMAKE_SOURCE_DIR}/cmake/InstallConfig.cmake)
