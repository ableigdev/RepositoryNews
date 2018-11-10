set(PATH_TO_QT "/path/to/your/Qt/" CACHE STRING "Path to Qt")
message(STATUS "Path to Qt(CMake): " ${PATH_TO_QT})
set(CMAKE_PREFIX_PATH ${PATH_TO_QT})
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)
# Create code from a list of Qt designer qrc files
set(CMAKE_AUTORCC ON)

# Find the QtWidgets library
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Multimedia CONFIG REQUIRED)

include_directories(${Qt5Widgets_INCLUDE_DIRS})
add_definitions(${Qt5Widgets_DEFINITIONS})
