include("${CMAKE_CURRENT_LIST_DIR}/MSVC.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/WinCore.cmake")

message(STATUS "Configuring Windows toolchain")
set(PONY_WINDOWS TRUE)
add_compile_definitions(PONY_WINDOWS)
