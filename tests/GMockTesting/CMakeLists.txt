cmake_minimum_required(VERSION 3.10)

project(GMockTesting)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} GMockTesting.cpp)

if(UNIX)
    # Target filesystem library
    target_link_libraries(${PROJECT_NAME} stdc++fs)
endif()

# Target qt and gtest libraries
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Multimedia)
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS_GTEST})
# Target libgit2 library
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CONAN_INCLUDE_DIRS_LIBGIT2}>)
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
