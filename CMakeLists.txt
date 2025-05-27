message(STATUS "Configuring PonyEngine environment")
cmake_minimum_required (VERSION 3.31)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY PONY_ENGINE_API)
set_property(GLOBAL PROPERTY PONY_ENGINE_INSTALL)
include("CMake/Compiler.cmake")

message(STATUS "Configuring project")
project("PonyEngineGame" LANGUAGES CXX)
init_build_options()

message(STATUS "Configuring engine")
add_subdirectory("Targets/Engine")
get_property(PONY_ENGINE_API_VALUE GLOBAL PROPERTY PONY_ENGINE_API)
message(STATUS "PonyEngine API: ${PONY_ENGINE_API_VALUE}")

message(STATUS "Configuring application")
add_subdirectory("Targets/Application")

message(STATUS "Installing")
get_property(PONY_ENGINE_INSTALL_VALUE GLOBAL PROPERTY PONY_ENGINE_INSTALL)
message(STATUS "Install list: ${PONY_ENGINE_INSTALL_VALUE}")
install(TARGETS ${PONY_ENGINE_INSTALL_VALUE} RUNTIME DESTINATION .)
