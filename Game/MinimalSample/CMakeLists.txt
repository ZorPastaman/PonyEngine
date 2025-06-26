cmake_minimum_required(VERSION 3.31)

# Set environment
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
set(CMAKE_CXX_MODULE_STD ON)
include(FetchContent)

# Set game project.
project(${PONY_PROJECT_NAME} VERSION ${PONY_PROJECT_VERSION} LANGUAGES CXX)

# Add PonyEngine project.
FetchContent_Declare(
  PonyEngine
  GIT_REPOSITORY https://github.com/ZorPastaman/PonyEngine
  GIT_TAG develop
)
FetchContent_MakeAvailable(PonyEngine)

# Set PonyEngine log defines.
pony_set_log_defines(PonyEngine.Core ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL} ${PONY_CONSOLE_LOG} ${PONY_PLATFORM_CONSOLE_LOG})
if(TARGET PonyEngine.Log.Ext)
	pony_set_log_defines(PonyEngine.Log.Ext ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL} ${PONY_CONSOLE_LOG} ${PONY_PLATFORM_CONSOLE_LOG})
endif()
if(TARGET PonyEngine.Log.Impl)
	pony_set_log_defines(PonyEngine.Log.Impl ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL} ${PONY_CONSOLE_LOG} ${PONY_PLATFORM_CONSOLE_LOG})
endif()
pony_set_log_defines(PonyEngine.Application ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL} ${PONY_CONSOLE_LOG} ${PONY_PLATFORM_CONSOLE_LOG})

# Set PonyEngine build options.
pony_set_build_options(PonyEngine.Core ${PONY_ENGINE_OPTIMIZATION})
if(TARGET PonyEngine.Log.Ext)
	pony_set_build_options(PonyEngine.Log.Ext ${PONY_ENGINE_OPTIMIZATION})
endif()
if(TARGET PonyEngine.Log.Impl)
	pony_set_build_options(PonyEngine.Log.Impl ${PONY_ENGINE_OPTIMIZATION})
endif()
pony_set_build_options(PonyEngine.Application ${PONY_ENGINE_OPTIMIZATION})

# Add game modules.
add_subdirectory("GameSample")
# Set Game log defines.
pony_set_log_defines(GameSample ${PONY_GAME_LOG_LEVEL} ${PONY_GAME_LOG_STACKTRACE_LEVEL} ${PONY_CONSOLE_LOG} ${PONY_PLATFORM_CONSOLE_LOG})
# Set Game build options.
pony_set_build_options(GameSample ${PONY_GAME_OPTIMIZATION})
# Add Game module to PonyEngine.
target_link_libraries(PonyEngine.Application PRIVATE GameSample)

# Install targets.
set(INSTALL_TARGETS "")
list(APPEND INSTALL_TARGETS PonyEngine.Application)
if(NOT PONY_ENGINE_FORCE_STATIC)
	list(APPEND INSTALL_TARGETS GameSample)
	if(TARGET PonyEngine.Log.Impl)
		list(APPEND INSTALL_TARGETS PonyEngine.Log.Impl)	
	endif()
endif()
install(TARGETS ${INSTALL_TARGETS}
	RUNTIME DESTINATION .
	LIBRARY DESTINATION
)
