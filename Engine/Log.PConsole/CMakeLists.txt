message(STATUS "Configuring PonyEngine.Log.PlatformConsole")

message(VERBOSE "Validating settings")
if(NOT PONY_WINCORE)
	message(FATAL_ERROR "PONY_ENGINE_LOG_PLATFORM_CONSOLE is set but the platform doesn't support it")
endif()

if(NOT PONY_ENGINE_LOG_PLATFORM_CONSOLE_ORDER)
	message(FATAL_ERROR "PONY_ENGINE_LOG_PLATFORM_CONSOLE is set but PONY_ENGINE_LOG_PLATFORM_CONSOLE_ORDER isn't")
endif()
if(NOT PONY_ENGINE_LOG_PLATFORM_CONSOLE_ORDER MATCHES "^-?[0-9]+$")
	message(FATAL_ERROR "PONY_ENGINE_LOG_PLATFORM_CONSOLE isn't a number")
endif()

if(NOT TARGET PonyEngine.Log.Extension)
	message(FATAL_ERROR "PonyEngine.Log.Extension wasn't configured")
endif()

message(VERBOSE "Configuring target")
add_library(PonyEngine.Log.PlatformConsole STATIC)

if(PONY_WINCORE)
	message(VERBOSE "Configuring headers for WinCore")
	target_include_directories(PonyEngine.Log.PlatformConsole  PUBLIC
		"Include/Public/WinCore"
	)
endif()

if(PONY_WINCORE)
	message(VERBOSE "Configuring sources for WinCore")
	target_sources(PonyEngine.Log.PlatformConsole PUBLIC
		"Source/Main.WinCore.cpp"
	)
	target_sources(PonyEngine.Log.PlatformConsole PRIVATE
		"Source/Main.WinCore.Impl.cpp"
	)
	target_sources(PonyEngine.Log.PlatformConsole PRIVATE FILE_SET CXX_MODULES FILES 
		"Source/Private/Log.PConsole/WinCore/Log.PConsole.WinCore.cppm"
		"Source/Private/Log.PConsole/WinCore/Log.PConsole.WinCore-PConsoleSubLogger.cppm"
		"Source/Private/Log.PConsole/WinCore/Log.PConsole.WinCore-PConsoleSubLoggerFactory.cppm"
		"Source/Private/Log.PConsole/WinCore/Log.PConsole.WinCore-PConsoleSubLoggerModule.cppm"
	)
endif()

message(VERBOSE "Configuring defines")
target_compile_definitions(PonyEngine.Log.PlatformConsole PRIVATE PONY_ENGINE_LOG_PLATFORM_CONSOLE_ORDER=${PONY_ENGINE_LOG_PLATFORM_CONSOLE_ORDER})

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Log.PlatformConsole PROPERTIES 
	CXX_STANDARD 23
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Log.PlatformConsole PUBLIC
	PonyEngine.Core
	PonyEngine.Log.Extension
)
