cmake_minimum_required(VERSION 3.10)

project(CreateNewGitRepository)
aux_source_directory(${CMAKE_SOURCE_DIR}/rpnews SRC_LIST)
#message(${SRC_LIST})

getSources(${CMAKE_SOURCE_DIR}/rpnews LIST)

#message(${LIST})

add_executable(CreateNewGitRepository ${LIST} CreateNewGitRepository.cpp)

# Target libgit2, qt and gtest libraries
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${LIBGIT2_INCLUDE}>)
target_link_libraries(${PROJECT_NAME} $<BUILD_INTERFACE:${LIBGIT2_LIBRARY}> googletest Qt5::Widgets)