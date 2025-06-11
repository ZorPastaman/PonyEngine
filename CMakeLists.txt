message(STATUS "Configuring PonyEngine environment")
if(${CMAKE_CURRENT_LIST_DIR} STREQUAL ${CMAKE_SOURCE_DIR}) # It's an engine build.
	cmake_minimum_required (VERSION 3.31)
	set(CMAKE_CXX_STANDARD 23)
	set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
	set(CMAKE_CXX_STANDARD_REQUIRED ON)
	set(CMAKE_CXX_MODULE_STD 1)
	set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)
	set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API 1)
endif()
add_subdirectory("CMake")
pony_init_install()
pony_set_std_build_options()
pony_init_platform()
pony_set_global_log_defines()
set_property(GLOBAL PROPERTY PONY_ENGINE_PATH "${CMAKE_CURRENT_LIST_DIR}/Engine")	

if(${CMAKE_CURRENT_LIST_DIR} STREQUAL ${CMAKE_SOURCE_DIR}) # It's an engine build.
	message(STATUS "Configuring project")
	project(${PONY_GAME_NAME} VERSION ${PONY_GAME_VERSION} LANGUAGES CXX)
	pony_clean_std_compile_flags()
	pony_init_build_options() # Must be done in a game build as well.

	message(STATUS "Configuring modules")
	get_property(PONY_ENGINE_PATH_VALUE GLOBAL PROPERTY PONY_ENGINE_PATH)
	add_subdirectory("${PONY_ENGINE_PATH_VALUE}/PonyEngine.Core")
	add_subdirectory("${PONY_ENGINE_PATH_VALUE}/PonyEngine.Log.Extension")
	add_subdirectory("${PONY_ENGINE_PATH_VALUE}/PonyEngine.Log.Implementation")

	message(STATUS "Configuring application")
	add_subdirectory("${PONY_ENGINE_PATH_VALUE}/PonyEngine.Application")

	message(STATUS "Configuring test project")
	project("PonyEngineTests")
	add_subdirectory("Tests")
endif()
