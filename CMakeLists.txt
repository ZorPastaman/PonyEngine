message(STATUS "Configuring PonyEngine environment")
cmake_minimum_required (VERSION 3.31)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_subdirectory("CMake")
pony_init_platform()
pony_set_global_log_defines()
set_property(GLOBAL PROPERTY PONY_ENGINE_PATH "${CMAKE_CURRENT_LIST_DIR}/Engine")

message(STATUS "Configuring project")
project("PonyEngineGame" VERSION 0.0.0.0 LANGUAGES CXX)
pony_init_build_options()

message(STATUS "Configuring modules")
get_property(PONY_ENGINE_PATH_VALUE GLOBAL PROPERTY PONY_ENGINE_PATH)
add_subdirectory("${PONY_ENGINE_PATH_VALUE}/PonyEngine.Core")
add_subdirectory("${PONY_ENGINE_PATH_VALUE}/PonyEngine.Log")

message(STATUS "Configuring application")
add_subdirectory("${PONY_ENGINE_PATH_VALUE}/PonyEngine.Application")

message(STATUS "Installing")
pony_install()

message(STATUS "Configuring test project")
project("PonyEngineTests")
add_subdirectory("Tests")
