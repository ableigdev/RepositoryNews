# Select project type
set(_PN ${PROJECT_NAME})

#Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Release'.")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
    
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
        "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

include(${CMAKE_SOURCE_DIR}/cmake/FindQt.cmake)

# Target
if(WIN32)
	add_executable(${PROJECT_NAME} WIN32 ${mainFile} ${SOURCES} ${HEADERS} ${UIS} ${RCS})
else()
	add_executable(${PROJECT_NAME} ${mainFile} ${SOURCES} ${HEADERS} ${UIS} ${RCS})
endif()

# Use the Widgets module from Qt 5
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Multimedia)
# Target libgit2 library
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CONAN_INCLUDE_DIRS_LIBGIT2}>)
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
# Target filesystem library
target_link_libraries(${PROJECT_NAME} stdc++fs)

# Install project
install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_EXPORT}
    RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
    COMPONENT dev)
