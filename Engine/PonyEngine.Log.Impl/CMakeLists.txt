message(STATUS "Configuring PonyEngine.Log.Impl")

message(VERBOSE "Validating settings")
if(NOT PONY_ENGINE_LOG_CORE AND NOT PONY_ENGINE_LOG_CONSOLE AND NOT PONY_ENGINE_LOG_PLATFORM_CONSOLE AND NOT PONY_ENGINE_LOG_FILE)
	message(FATAL_ERROR "No part of PonyEngine.Log.Impl is set")
endif()

if(PONY_ENGINE_LOG_CONSOLE)
	if(NOT PONY_ENGINE_LOG_CONSOLE_ORDER)
		message(FATAL_ERROR "PONY_ENGINE_LOG_CONSOLE is set but PONY_ENGINE_LOG_CONSOLE_ORDER isn't")
	endif()
	if(NOT PONY_ENGINE_LOG_CONSOLE_ORDER MATCHES "^-?[0-9]+$")
		message(FATAL_ERROR "PONY_ENGINE_LOG_CONSOLE_ORDER isn't a number")
	endif()
endif()

if(PONY_ENGINE_LOG_PLATFORM_CONSOLE)
	if(NOT PONY_WINCORE)
		message(FATAL_ERROR "PONY_ENGINE_LOG_PLATFORM_CONSOLE is set but the platform doesn't support it")
	endif()

	if(NOT PONY_ENGINE_LOG_PLATFORM_CONSOLE_ORDER)
		message(FATAL_ERROR "PONY_ENGINE_LOG_PLATFORM_CONSOLE is set but PONY_ENGINE_LOG_PLATFORM_CONSOLE_ORDER isn't")
	endif()
	if(NOT PONY_ENGINE_LOG_PLATFORM_CONSOLE_ORDER MATCHES "^-?[0-9]+$")
		message(FATAL_ERROR "PONY_ENGINE_LOG_PLATFORM_CONSOLE isn't a number")
	endif()
endif()

if(PONY_ENGINE_LOG_FILE)
	if(NOT PONY_ENGINE_LOG_FILE_ORDER)
		message(FATAL_ERROR "PONY_ENGINE_LOG_FILE is set but PONY_ENGINE_LOG_FILE_ORDER isn't")
	endif()
	if(NOT PONY_ENGINE_LOG_FILE_ORDER MATCHES "^-?[0-9]+$")
		message(FATAL_ERROR "PONY_ENGINE_LOG_FILE_ORDER isn't a number")
	endif()

	if(NOT PONY_ENGINE_LOG_FILE_PATH)
		message(FATAL_ERROR "PONY_ENGINE_LOG_FILE is set but PONY_ENGINE_LOG_FILE_PATH isn't")
	endif()
	if(IS_ABSOLUTE PONY_ENGINE_LOG_FILE_PATH)
		message(FATAL_ERROR "PONY_ENGINE_LOG_FILE_PATH isn't relative")
	endif()
	if(NOT PONY_ENGINE_LOG_FILE_PATH MATCHES "^[A-Za-z0-9._/-]+$")
		message(FATAL_ERROR "PONY_ENGINE_LOG_FILE_PATH contains invalid symbols")
	endif()
	foreach(path_component IN LISTS PONY_ENGINE_LOG_FILE_PATH)
		string(TOLOWER "${path_component}" path_component_lower)
		if("${path_component_lower}" MATCHES "^(con|prn|aux|nul|com[1-9]|lpt[1-9])(\\..*)?$")
			message(FATAL_ERROR "PONY_ENGINE_LOG_FILE_PATH contains invalid component names")
		endif()
	endforeach()
endif()

if(NOT TARGET PonyEngine.Log.Ext)
	message(FATAL_ERROR "PonyEngine.Log.Extension wasn't configured")
endif()

if(PONY_ENGINE_FORCE_STATIC)
	message(VERBOSE "Configuring target as static")
	add_library(PonyEngine.Log.Impl STATIC)
else()
	message(VERBOSE "Configuring target as shared")
	add_library(PonyEngine.Log.Impl SHARED)
endif()

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.Log.Impl PUBLIC
	"Include/Public"
)

if(PONY_ENGINE_LOG_CORE)
	message(VERBOSE "Configuring core sources")
	target_sources(PonyEngine.Log.Impl PUBLIC
		"Source/Main.Logger.cpp"
	)
	target_sources(PonyEngine.Log.Impl PRIVATE
		"Source/Main.Logger.Impl.cpp"
	)
	target_sources(PonyEngine.Log.Impl PRIVATE FILE_SET CXX_MODULES FILES 
		"Source/Private/Log.Core/Log.Core.cppm"
		"Source/Private/Log.Core/Log.Core-Logger.cppm"
		"Source/Private/Log.Core/Log.Core-LoggerFactory.cppm"
		"Source/Private/Log.Core/Log.Core-LoggerModule.cppm"
	)
endif()
if(PONY_ENGINE_LOG_CONSOLE)
	message(VERBOSE "Configuring console sources")
	target_sources(PonyEngine.Log.Impl PUBLIC
		"Source/Main.Console.cpp"
	)
	target_sources(PonyEngine.Log.Impl PRIVATE
		"Source/Main.Console.Impl.cpp"
	)
	target_sources(PonyEngine.Log.Impl PRIVATE FILE_SET CXX_MODULES FILES 
		"Source/Private/Log.Console/Log.Console.cppm"
		"Source/Private/Log.Console/Log.Console-ConsoleSubLogger.cppm"
		"Source/Private/Log.Console/Log.Console-ConsoleSubLoggerFactory.cppm"
		"Source/Private/Log.Console/Log.Console-ConsoleSubLoggerModule.cppm"
	)
endif()
if(PONY_ENGINE_LOG_PLATFORM_CONSOLE)
	message(VERBOSE "Configuring plaform console sources")
	if(PONY_WINCORE)
		message(VERBOSE "Configuring plaform console sources for WinCore")
		target_sources(PonyEngine.Log.Impl PUBLIC
			"Source/Main.PConsole.WinCore.cpp"
		)
		target_sources(PonyEngine.Log.Impl PRIVATE
			"Source/Main.PConsole.WinCore.Impl.cpp"
		)
		target_sources(PonyEngine.Log.Impl PRIVATE FILE_SET CXX_MODULES FILES 
			"Source/Private/Log.PConsole/WinCore/Log.PConsole.WinCore.cppm"
			"Source/Private/Log.PConsole/WinCore/Log.PConsole.WinCore-PConsoleSubLogger.cppm"
			"Source/Private/Log.PConsole/WinCore/Log.PConsole.WinCore-PConsoleSubLoggerFactory.cppm"
			"Source/Private/Log.PConsole/WinCore/Log.PConsole.WinCore-PConsoleSubLoggerModule.cppm"
		)
	endif()
endif()
if(PONY_ENGINE_LOG_FILE)
	message(VERBOSE "Configuring file sources")
	target_sources(PonyEngine.Log.Impl PUBLIC
		"Source/Main.File.cpp"
	)
	target_sources(PonyEngine.Log.Impl PRIVATE
		"Source/Main.File.Impl.cpp"
	)
	target_sources(PonyEngine.Log.Impl PRIVATE FILE_SET CXX_MODULES FILES 
		"Source/Private/Log.File/Log.File.cppm"
		"Source/Private/Log.File/Log.File-FileSubLogger.cppm"
		"Source/Private/Log.File/Log.File-FileSubLoggerFactory.cppm"
		"Source/Private/Log.File/Log.File-FileSubLoggerModule.cppm"
	)
endif()

message(VERBOSE "Configuring defines")
if(PONY_ENGINE_LOG_CONSOLE)
	target_compile_definitions(PonyEngine.Log.Impl PRIVATE PONY_ENGINE_LOG_CONSOLE_ORDER=${PONY_ENGINE_LOG_CONSOLE_ORDER})
endif()
if(PONY_ENGINE_LOG_PLATFORM_CONSOLE)
	target_compile_definitions(PonyEngine.Log.Impl PRIVATE PONY_ENGINE_LOG_PLATFORM_CONSOLE_ORDER=${PONY_ENGINE_LOG_PLATFORM_CONSOLE_ORDER})
endif()
if(PONY_ENGINE_LOG_FILE)
	target_compile_definitions(PonyEngine.Log.Impl PRIVATE PONY_ENGINE_LOG_FILE_ORDER=${PONY_ENGINE_LOG_FILE_ORDER})
	target_compile_definitions(PonyEngine.Log.Impl PRIVATE PONY_ENGINE_LOG_FILE_PATH=${PONY_ENGINE_LOG_FILE_PATH})
endif()
if(NOT PONY_FORCE_STATIC)
	target_compile_definitions(PonyEngine.Log.Impl PRIVATE PONY_DLL)
endif()

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Log.Impl PROPERTIES CXX_STANDARD 23)
set_target_properties(PonyEngine.Log.Impl PROPERTIES OUTPUT_NAME "PonyEngine.Log")

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Log.Impl PRIVATE
	PonyEngine.Core
	PonyEngine.Log.Ext
)
