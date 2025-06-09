message(STATUS "Configuring PonyEngine environment")
if(${CMAKE_CURRENT_LIST_DIR} STREQUAL ${CMAKE_SOURCE_DIR}) # It's an engine build.
	cmake_minimum_required (VERSION 3.31)
	set(CMAKE_CXX_STANDARD 20)
	set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()
add_subdirectory("CMake")
pony_init_install()
pony_init_platform()
pony_set_global_log_defines()
set_property(GLOBAL PROPERTY PONY_ENGINE_PATH "${CMAKE_CURRENT_LIST_DIR}/Engine")

if(${CMAKE_CURRENT_LIST_DIR} STREQUAL ${CMAKE_SOURCE_DIR}) # It's an engine build.
	message(STATUS "Configuring project")
	project("PonyEngineGame" VERSION 0.0.0.0 LANGUAGES CXX)
	pony_init_build_options() # Must be done in a game build as well.

	message(STATUS "Configuring modules")
	get_property(PONY_ENGINE_PATH_VALUE GLOBAL PROPERTY PONY_ENGINE_PATH)
	add_subdirectory("${PONY_ENGINE_PATH_VALUE}/PonyEngine.Core")
	add_subdirectory("${PONY_ENGINE_PATH_VALUE}/PonyEngine.Log.Ext")
	add_subdirectory("${PONY_ENGINE_PATH_VALUE}/PonyEngine.Log.Impl")

	message(STATUS "Configuring application")
	add_subdirectory("${PONY_ENGINE_PATH_VALUE}/PonyEngine.Application")

	message(STATUS "Configuring test project")
	project("PonyEngineTests")
	add_subdirectory("Tests")
endif()
