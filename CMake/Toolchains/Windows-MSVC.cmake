message(STATUS "Configuring Windows x64 MSVC toolchain")

message(VERBOSE "Configuring platform")
include("${CMAKE_CURRENT_LIST_DIR}/Windows.cmake")

message(VERBOSE "Configuring compiler")
include("${CMAKE_CURRENT_LIST_DIR}/MSVC.cmake")
