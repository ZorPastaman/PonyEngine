cmake_minimum_required(VERSION 3.31)

# Set environment
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
set(CMAKE_CXX_MODULE_STD ON)
include(FetchContent)

# Set game project.
project(${PONY_PROJECT_NAME} VERSION ${PONY_PROJECT_VERSION} LANGUAGES CXX)
pony_clean_build_options()

set(PONY_ENGINE_APPLICATION_MAIN TRUE)

# Add PonyEngine project.
message(STATUS "Fetching PonyEngine")
FetchContent_Declare(
  PonyEngine
  GIT_REPOSITORY https://github.com/ZorPastaman/PonyEngine
  GIT_TAG develop
)
FetchContent_MakeAvailable(PonyEngine)

# Group modules
set(PONY_BASE_MODULES "")
set(PONY_DEBUG_MODULES "")
set(PONY_GAME_MODULES "")

# Set PonyEngine options.
pony_set_log_defines(PonyEngine.Core ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL} ${PONY_CONSOLE_LOG})
pony_set_build_options(PonyEngine.Core ${PONY_ENGINE_OPTIMIZATION})
pony_set_log_defines(PonyEngine.Log ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL})
pony_set_build_options(PonyEngine.Log ${PONY_ENGINE_OPTIMIZATION})
pony_set_log_defines(PonyEngine.Application.Extension ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL} ${PONY_CONSOLE_LOG} ${PONY_PLATFORM_CONSOLE_LOG})
pony_set_build_options(PonyEngine.Application.Extension ${PONY_ENGINE_OPTIMIZATION})
pony_set_log_defines(PonyEngine.Application.Main ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL} ${PONY_CONSOLE_LOG} ${PONY_PLATFORM_CONSOLE_LOG})
pony_set_build_options(PonyEngine.Application.Main ${PONY_ENGINE_OPTIMIZATION})
if(TARGET PonyEngine.Surface)
	pony_set_log_defines(PonyEngine.Surface ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL} ${PONY_CONSOLE_LOG} ${PONY_PLATFORM_CONSOLE_LOG})
	pony_set_build_options(PonyEngine.Surface ${PONY_ENGINE_OPTIMIZATION})
endif()
if(TARGET PonyEngine.Surface.Main)
	pony_set_log_defines(PonyEngine.Surface.Main ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL} ${PONY_CONSOLE_LOG} ${PONY_PLATFORM_CONSOLE_LOG})
	pony_set_build_options(PonyEngine.Surface.Main ${PONY_ENGINE_OPTIMIZATION})
	list(APPEND PONY_BASE_MODULES PonyEngine.Surface.Main)
endif()
if(TARGET PonyEngine.Log.Extension)
	pony_set_log_defines(PonyEngine.Log.Extension ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL} ${PONY_CONSOLE_LOG} ${PONY_PLATFORM_CONSOLE_LOG})
	pony_set_build_options(PonyEngine.Log.Extension ${PONY_ENGINE_OPTIMIZATION})
endif()
if(TARGET PonyEngine.Log.Main)
	pony_set_log_defines(PonyEngine.Log.Main ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL} ${PONY_CONSOLE_LOG} ${PONY_PLATFORM_CONSOLE_LOG})
	pony_set_build_options(PonyEngine.Log.Main ${PONY_ENGINE_OPTIMIZATION})
	list(APPEND PONY_DEBUG_MODULES PonyEngine.Log.Main)
endif()
if(TARGET PonyEngine.Log.File)
	pony_set_log_defines(PonyEngine.Log.File ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL} ${PONY_CONSOLE_LOG} ${PONY_PLATFORM_CONSOLE_LOG})
	pony_set_build_options(PonyEngine.Log.File ${PONY_ENGINE_OPTIMIZATION})
	list(APPEND PONY_DEBUG_MODULES PonyEngine.Log.File)
endif()

# Add game modules.
add_subdirectory("GameSample")
# Set Game options.
pony_set_log_defines(GameSample ${PONY_GAME_LOG_LEVEL} ${PONY_GAME_LOG_STACKTRACE_LEVEL} ${PONY_CONSOLE_LOG} ${PONY_PLATFORM_CONSOLE_LOG})
pony_set_build_options(GameSample ${PONY_GAME_OPTIMIZATION})
list(APPEND PONY_GAME_MODULES GameSample)

# Create groups, link to the application and make install list.
set(PONY_INSTALL_TARGETS "")
if(PONY_MAKE_GROUPS)
	if(PONY_BASE_MODULES)
		pony_make_module_group(PONY_BASE_MODULES PonyEngine.Base.Group "PonyEngine.Base" 23)
		pony_set_log_defines(PonyEngine.Base.Group ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL} ${PONY_CONSOLE_LOG} ${PONY_PLATFORM_CONSOLE_LOG})
		pony_set_build_options(PonyEngine.Base.Group ${PONY_ENGINE_OPTIMIZATION})
		target_link_libraries(PonyEngine.Application.Main PRIVATE PonyEngine.Base.Group)
		list(APPEND PONY_INSTALL_TARGETS PonyEngine.Base.Group)
	endif()

	if(PONY_DEBUG_MODULES)
		pony_make_module_group(PONY_DEBUG_MODULES PonyEngine.Debug.Group "PonyEngine.Debug" 23)
		pony_set_log_defines(PonyEngine.Debug.Group ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL} ${PONY_CONSOLE_LOG} ${PONY_PLATFORM_CONSOLE_LOG})
		pony_set_build_options(PonyEngine.Debug.Group ${PONY_ENGINE_OPTIMIZATION})
		target_link_libraries(PonyEngine.Application.Main PRIVATE PonyEngine.Debug.Group)
		list(APPEND PONY_INSTALL_TARGETS PonyEngine.Debug.Group)
	endif()

	pony_make_module_group(PONY_GAME_MODULES PonyEngine.Game.Group "PonyEngine.Game" 23)
	pony_set_log_defines(PonyEngine.Game.Group ${PONY_GAME_LOG_LEVEL} ${PONY_GAME_LOG_STACKTRACE_LEVEL} ${PONY_CONSOLE_LOG} ${PONY_PLATFORM_CONSOLE_LOG})
	pony_set_build_options(PonyEngine.Game.Group ${PONY_GAME_OPTIMIZATION})
	target_link_libraries(PonyEngine.Application.Main PRIVATE PonyEngine.Game.Group)
	list(APPEND PONY_INSTALL_TARGETS PonyEngine.Game.Group)
else()
	target_link_libraries(PonyEngine.Application.Main PRIVATE 
		${PONY_BASE_MODULES}
		${PONY_DEBUG_MODULES}
		${PONY_GAME_MODULES}
	)
endif()
list(APPEND PONY_INSTALL_TARGETS PonyEngine.Application.Main)

# Install targets.
message(STATUS "Install list: ${PONY_INSTALL_TARGETS}")
install(TARGETS ${PONY_INSTALL_TARGETS}
	RUNTIME DESTINATION .
	LIBRARY DESTINATION
)
