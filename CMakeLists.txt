message(STATUS "Configuring environment")
cmake_minimum_required (VERSION 3.31)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(${CMAKE_SOURCE_DIR}/cmake/Compiler.cmake)

message(STATUS "Configuring project")
project("PonyEngineGame" LANGUAGES CXX)
init_compile_options()

message(STATUS "Configuring main application")
add_subdirectory("Targets/Application/Application.Core")
