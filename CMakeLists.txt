message(STATUS "Configuring environment")
cmake_minimum_required (VERSION 3.31)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(${CMAKE_SOURCE_DIR}/cmake/Compiler.cmake)

message(STATUS "Configuring project")
project("PonyEngineGame" LANGUAGES CXX)
init_build_options()

message(STATUS "Configuring main application")
add_subdirectory("Targets/Application/Core")

message(STATUS "Installing")
install(TARGETS PonyApplication RUNTIME DESTINATION .)
