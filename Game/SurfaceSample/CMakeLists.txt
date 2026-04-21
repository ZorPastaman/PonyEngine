cmake_minimum_required(VERSION 3.31)

# Set environment
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
set(CMAKE_CXX_MODULE_STD ON)
include(FetchContent)

# Set game project.
project(${PONY_PROJECT_NAME} VERSION "${PONY_PROJECT_VERSION_MAJOR}.${PONY_PROJECT_VERSION_MINOR}.${PONY_PROJECT_VERSION_PATCH}.${PONY_PROJECT_VERSION_TWEAK}" LANGUAGES CXX)
pony_clean_build_options()

# Add PonyEngine project.
message(STATUS "Fetching PonyEngine")
FetchContent_Declare(
	PonyEngine
	GIT_REPOSITORY https://github.com/ZorPastaman/PonyEngine.git
	GIT_TAG v0.1.1
)
FetchContent_MakeAvailable(PonyEngine)

# Group modules
set(PONY_LOG_MODULES "")
set(PONY_PLATFORM_MODULES "")
set(PONY_INPUT_MODULES "")

# Set PonyEngine options.
pony_set_build_options(PonyEngine.Core ${PONY_ENGINE_OPTIMIZATION})
pony_set_log_defines(PonyEngine.Log ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL})
pony_set_build_options(PonyEngine.Log ${PONY_ENGINE_OPTIMIZATION})
pony_set_log_defines(PonyEngine.Application.Ext ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL})
pony_set_build_options(PonyEngine.Application.Ext ${PONY_ENGINE_OPTIMIZATION})
pony_set_log_defines(PonyEngine.Application.Impl ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL})
pony_set_build_options(PonyEngine.Application.Impl ${PONY_ENGINE_OPTIMIZATION})

if(TARGET PonyEngine.Log.Ext)
	pony_set_log_defines(PonyEngine.Log.Ext ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL})
	pony_set_build_options(PonyEngine.Log.Ext ${PONY_ENGINE_OPTIMIZATION})
endif()
if(TARGET PonyEngine.Log.Impl)
	pony_set_log_defines(PonyEngine.Log.Impl ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL})
	pony_set_build_options(PonyEngine.Log.Impl ${PONY_ENGINE_OPTIMIZATION})
	list(APPEND PONY_LOG_MODULES PonyEngine.Log.Impl)
endif()
if(TARGET PonyEngine.Log.File.Impl)
	pony_set_log_defines(PonyEngine.Log.File.Impl ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL})
	pony_set_build_options(PonyEngine.Log.File.Impl ${PONY_ENGINE_OPTIMIZATION})
	list(APPEND PONY_LOG_MODULES PonyEngine.Log.File.Impl)
endif()

if(TARGET PonyEngine.MessagePump)
	pony_set_log_defines(PonyEngine.MessagePump ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL})
	pony_set_build_options(PonyEngine.MessagePump ${PONY_ENGINE_OPTIMIZATION})
endif()
if(TARGET PonyEngine.MessagePump.Impl)
	pony_set_log_defines(PonyEngine.MessagePump.Impl ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL})
	pony_set_build_options(PonyEngine.MessagePump.Impl ${PONY_ENGINE_OPTIMIZATION})
	list(APPEND PONY_PLATFORM_MODULES PonyEngine.MessagePump.Impl)
endif()

if(TARGET PonyEngine.Surface)
	pony_set_log_defines(PonyEngine.Surface ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL})
	pony_set_build_options(PonyEngine.Surface ${PONY_ENGINE_OPTIMIZATION})
endif()
if(TARGET PonyEngine.Surface.Impl)
	pony_set_log_defines(PonyEngine.Surface.Impl ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL})
	pony_set_build_options(PonyEngine.Surface.Impl ${PONY_ENGINE_OPTIMIZATION})
	list(APPEND PONY_PLATFORM_MODULES PonyEngine.Surface.Impl)
endif()

if(TARGET PonyEngine.RawInput)
	pony_set_log_defines(PonyEngine.RawInput ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL})
	pony_set_build_options(PonyEngine.RawInput ${PONY_ENGINE_OPTIMIZATION})
endif()
if(TARGET PonyEngine.RawInput.Ext)
	pony_set_log_defines(PonyEngine.RawInput.Ext ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL})
	pony_set_build_options(PonyEngine.RawInput.Ext ${PONY_ENGINE_OPTIMIZATION})
endif()
if(TARGET PonyEngine.RawInput.Impl)
	pony_set_log_defines(PonyEngine.RawInput.Impl ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL})
	pony_set_build_options(PonyEngine.RawInput.Impl ${PONY_ENGINE_OPTIMIZATION})
	list(APPEND PONY_INPUT_MODULES PonyEngine.RawInput.Impl)
endif()
if(TARGET PonyEngine.RawInput.Keyboard.Impl)
	pony_set_log_defines(PonyEngine.RawInput.Keyboard.Impl ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL})
	pony_set_build_options(PonyEngine.RawInput.Keyboard.Impl ${PONY_ENGINE_OPTIMIZATION})
	list(APPEND PONY_INPUT_MODULES PonyEngine.RawInput.Keyboard.Impl)
endif()
if(TARGET PonyEngine.RawInput.Mouse.Impl)
	pony_set_log_defines(PonyEngine.RawInput.Mouse.Impl ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL})
	pony_set_build_options(PonyEngine.RawInput.Mouse.Impl ${PONY_ENGINE_OPTIMIZATION})
	list(APPEND PONY_INPUT_MODULES PonyEngine.RawInput.Mouse.Impl)
endif()

# Add game modules.
add_subdirectory("GameSample")
# Set Game options.
pony_set_log_defines(GameSample ${PONY_GAME_LOG_LEVEL} ${PONY_GAME_LOG_STACKTRACE_LEVEL})
pony_set_build_options(GameSample ${PONY_GAME_OPTIMIZATION})
list(APPEND PONY_GAME_MODULES GameSample)

# Create groups, link to the application and make install list.
set(PONY_INSTALL_TARGETS PonyEngine.Application.Impl)
if(PONY_MAKE_GROUPS)
	message(VERBOSE "Making application module groups")
	if(PONY_LOG_MODULES)
		pony_make_module_group(PONY_LOG_MODULES PonyModule.Log "PonyModule.Log" 23)
		pony_set_log_defines(PonyModule.Log ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL})
		pony_set_build_options(PonyModule.Log ${PONY_ENGINE_OPTIMIZATION})
		target_link_libraries(PonyEngine.Application.Impl PRIVATE PonyModule.Log)
		list(APPEND PONY_INSTALL_TARGETS PonyModule.Log)
	endif()

	if(PONY_PLATFORM_MODULES)
		pony_make_module_group(PONY_PLATFORM_MODULES PonyModule.Platform "PonyModule.Platform" 23)
		pony_set_log_defines(PonyModule.Platform ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL})
		pony_set_build_options(PonyModule.Platform ${PONY_ENGINE_OPTIMIZATION})
		target_link_libraries(PonyEngine.Application.Impl PRIVATE PonyModule.Platform)
		list(APPEND PONY_INSTALL_TARGETS PonyModule.Platform)
	endif()

	if(PONY_INPUT_MODULES)
		pony_make_module_group(PONY_INPUT_MODULES PonyModule.Input "PonyModule.Input" 23)
		pony_set_log_defines(PonyModule.Input ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL})
		pony_set_build_options(PonyModule.Input ${PONY_ENGINE_OPTIMIZATION})
		target_link_libraries(PonyEngine.Application.Impl PRIVATE PonyModule.Input)
		list(APPEND PONY_INSTALL_TARGETS PonyModule.Input)
	endif()

	if(PONY_GAME_MODULES)
		pony_make_module_group(PONY_GAME_MODULES PonyModule.Game "PonyModule.Game" 23)
		pony_set_log_defines(PonyModule.Game ${PONY_GAME_LOG_LEVEL} ${PONY_GAME_LOG_STACKTRACE_LEVEL})
		pony_set_build_options(PonyModule.Game ${PONY_GAME_OPTIMIZATION})
		target_link_libraries(PonyEngine.Application.Impl PRIVATE PonyModule.Game)
		list(APPEND PONY_INSTALL_TARGETS PonyModule.Game)
	endif()
else()
	message(VERBOSE "Adding application modules")
	target_link_libraries(PonyEngine.Application.Impl PRIVATE
		${PONY_LOG_MODULES}
		${PONY_PLATFORM_MODULES}
		${PONY_INPUT_MODULES}
		${PONY_GAME_MODULES}
	)
endif()

# Install targets.
message(STATUS "Install list: ${PONY_INSTALL_TARGETS}")
install(TARGETS ${PONY_INSTALL_TARGETS}
	RUNTIME DESTINATION .
	LIBRARY DESTINATION
)
