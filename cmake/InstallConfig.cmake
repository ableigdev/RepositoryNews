# Uninstall targets
configure_file("${CMAKE_SOURCE_DIR}/cmake/Uninstall.cmake.in"
    "${PROJECT_CMAKE_FILES}/Uninstall.cmake"
    IMMEDIATE @ONLY)
add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${PROJECT_CMAKE_FILES}/Uninstall.cmake)
