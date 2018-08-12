# Set PROJECT_NAME_UPPERCASE and PROJECT_NAME_LOWERCASE variables
string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPERCASE)
string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWERCASE)

# Version variables
set(MAJOR_VERSION 0)
set(MINOR_VERSION 1)
set(PATCH_VERSION 0)
set(PROJECT_VERSION ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION})

# INSTALL_BIN_DIR
set(INSTALL_BIN_DIR bin
    CACHE PATH "Relative instalation path for executables")

# INSTALL_CMAKE_DIR
if(WIN32 AND NOT CYGWIN)
    set(DEF_INSTALL_CMAKE_DIR CMake)
else()
    set(DEF_INSTALL_CMAKE_DIR lib/CMake/${PROJECT_NAME})
endif()
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} 
    CACHE PATH "Relative instalation path for CMake files")

# TODO: Convert relative path to absolute path (needed later on)

# Set up include-directories
include_directories(
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_BINARY_DIR}")
  
# The export set for all the targets
set(PROJECT_EXPORT ${PROJECT_NAME}EXPORT)

# Path of the CNake files generated
set(PROJECT_CMAKE_FILES ${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY})

# The RPATH to be used when installing
set(CMAKE_INSTALL_RPATH ${INSTALL_LIB_DIR})
