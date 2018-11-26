cmake_minimum_required(VERSION 3.10)

include(${CMAKE_SOURCE_DIR}/cmake/FindQt.cmake)

include_directories(${CONAN_INCLUDE_DIRS_GTEST})

function(getSources input output)
    file(GLOB SRC_LIST ${input}/*.cpp ${input}/*/*.cpp)
    SET(listVar "")
    foreach(currentFile ${SRC_LIST})
        if (${currentFile} MATCHES "/main.cpp")
        else()
            LIST(APPEND listVar ${currentFile})
        endif ()
    endforeach()
    set(${output} ${listVar} PARENT_SCOPE)
endfunction(getSources)

add_subdirectory(CreateNewGitRepository)
add_subdirectory(TestHelpers)
