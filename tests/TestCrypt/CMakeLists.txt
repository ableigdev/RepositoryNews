cmake_minimum_required(VERSION 3.10)

project(TestCrypt)
getSources(${CMAKE_SOURCE_DIR}/rpnews/* SRC_LIST)

add_executable(TestCrypt ${SRC_LIST} TestCrypt.cpp)

# Target qt and gtest libraries
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Multimedia)
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS_GTEST})
# Target libgit2 library
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CONAN_INCLUDE_DIRS_LIBGIT2}>)
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
 
