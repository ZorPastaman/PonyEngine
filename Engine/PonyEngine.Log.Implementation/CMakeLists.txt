message(STATUS "Configuring PonyEngine.Log.Implementation")
if(PONY_FORCE_STATIC)
	add_library(PonyEngine.Log.Implementation STATIC)
else()
	add_library(PonyEngine.Log.Implementation SHARED)
endif()

message(STATUS "Configuring headers")
target_include_directories(PonyEngine.Log.Implementation PUBLIC
	"Include/Public"
)

if(PONY_ENGINE_LOG_CORE)
	message(STATUS "Configuring core sources")
	target_sources(PonyEngine.Log.Implementation PUBLIC
		"Source/Main.Logger.cpp"
	)
	target_sources(PonyEngine.Log.Implementation PRIVATE
		"Source/Main.Logger.Implementation.cpp"
	)
	target_sources(PonyEngine.Log.Implementation PRIVATE FILE_SET CXX_MODULES FILES 
		"Source/Private/Log.Core/Log.Core.cppm"
		"Source/Private/Log.Core/Log.Core-Logger.cppm"
		"Source/Private/Log.Core/Log.Core-LoggerFactory.cppm"
		"Source/Private/Log.Core/Log.Core-LoggerModule.cppm"
	)
endif()
if(PONY_ENGINE_LOG_CONSOLE)
	message(STATUS "Configuring console sources")
	target_sources(PonyEngine.Log.Implementation PUBLIC
		"Source/Main.Console.cpp"
	)
	target_sources(PonyEngine.Log.Implementation PRIVATE
		"Source/Main.Console.Implementation.cpp"
	)
	target_sources(PonyEngine.Log.Implementation PRIVATE FILE_SET CXX_MODULES FILES 
		"Source/Private/Log.Console/Log.Console.cppm"
		"Source/Private/Log.Console/Log.Console-ConsoleSubLogger.cppm"
		"Source/Private/Log.Console/Log.Console-ConsoleSubLoggerFactory.cppm"
		"Source/Private/Log.Console/Log.Console-ConsoleSubLoggerModule.cppm"
	)
endif()
if(PONY_ENGINE_LOG_PLATFORM_CONSOLE)
	if(PONY_WINCORE)
		target_sources(PonyEngine.Log.Implementation PUBLIC
			"Source/Main.PlatformConsole.WinCore.cpp"
		)
		target_sources(PonyEngine.Log.Implementation PRIVATE
			"Source/Main.PlatformConsole.WinCore.Implementation.cpp"
		)
		message(STATUS "Configuring platform console sources for WinCore")
		target_sources(PonyEngine.Log.Implementation PRIVATE FILE_SET CXX_MODULES FILES 
			"Source/Private/Log.PlatformConsole/WinCore/Log.PlatformConsole.WinCore.cppm"
			"Source/Private/Log.PlatformConsole/WinCore/Log.PlatformConsole.WinCore-PlatformConsoleSubLogger.cppm"
			"Source/Private/Log.PlatformConsole/WinCore/Log.PlatformConsole.WinCore-PlatformConsoleSubLoggerFactory.cppm"
			"Source/Private/Log.PlatformConsole/WinCore/Log.PlatformConsole.WinCore-PlatformConsoleSubLoggerModule.cppm"
		)
	endif()
endif()

message(STATUS "Configuring defines")
pony_set_log_mask(PonyEngine.Log.Implementation TRUE)
if(NOT PONY_FORCE_STATIC)
	target_compile_definitions(PonyEngine.Log.Implementation PRIVATE PONY_DLL)
endif()

message(STATUS "Setting properties")
set_target_properties(PonyEngine.Log.Implementation PROPERTIES OUTPUT_NAME "PonyEngine.Log")

message(STATUS "Setting build options")
pony_set_build_options(PonyEngine.Log.Implementation TRUE)
set_target_properties(PonyEngine.Log.Implementation PROPERTIES CXX_STANDARD 23)

message(STATUS "Configuring dependencies")
target_link_libraries(PonyEngine.Log.Implementation PRIVATE
	PonyEngine.Core
	PonyEngine.Log.Extension
)
pony_add_app_module(PonyEngine.Log.Implementation)

if(NOT PONY_FORCE_STATIC)
	message(STATUS "Installing")
	get_property(PONY_APP_INSTALL_PATH_VALUE GLOBAL PROPERTY PONY_APP_INSTALL_PATH)
	message(STATUS "Application destination: ${PONY_APP_INSTALL_PATH_VALUE}")
	install(TARGETS PonyEngine.Log.Implementation 
		RUNTIME DESTINATION ${PONY_APP_INSTALL_PATH_VALUE}
		LIBRARY DESTINATION
	)
endif()
