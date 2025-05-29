message(STATUS "Configuring PonyEngine environment")
cmake_minimum_required (VERSION 3.31)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY PONY_INSTALL)
include("CMake/Compiler.cmake")
if(PONY_WINCORE)
	add_compile_definitions(PONY_WINCORE)
endif()
if(PONY_WINDOWS)
	add_compile_definitions(PONY_WINDOWS)
endif()

message(STATUS "Configuring project")
project("PonyEngineGame" VERSION 0.0.0.0 LANGUAGES CXX)
init_build_options()

message(STATUS "Configuring modules")
add_subdirectory("Targets/Modules/PonyEngine.Core")

message(STATUS "Configuring application modules")

message(STATUS "Configuring application")
add_subdirectory("Targets/Application/PonyEngine.Application")

message(STATUS "Installing")
get_property(PONY_INSTALL_VALUE GLOBAL PROPERTY PONY_INSTALL)
message(STATUS "Install list: ${PONY_INSTALL_VALUE}")
install(TARGETS ${PONY_INSTALL_VALUE} RUNTIME DESTINATION .)
