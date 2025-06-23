message(STATUS "Configuring PonyEngine.Core")

message(VERBOSE "Configuring environment")
include("CMake/Log.cmake")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Core STATIC)

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.Core PUBLIC 
	"Include/Public/Common"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Core PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Public/Application/Application.cppm"
	"Source/Public/Application/Application-ApplicationPaths.cppm"
	"Source/Public/Application/Application-IApplicationContext.cppm"
	"Source/Public/Core/Core.cppm"
	"Source/Public/Core/Core-IEngine.cppm"
	"Source/Public/Core/Core-IEngineFactory.cppm"
	"Source/Public/Core/Core-ILogger.cppm"
	"Source/Public/Core/Core-ILoggerFactory.cppm"
	"Source/Public/Core/Core-IModule.cppm"
	"Source/Public/Core/Core-IModuleContext.cppm"
	"Source/Public/Engine/Engine.cppm"
	"Source/Public/Engine/Engine-IEngine.cppm"
	"Source/Public/Log/Log.cppm"
	"Source/Public/Log/Log-ILogger.cppm"
	"Source/Public/Log/Log-LogData.cppm"
	"Source/Public/Log/Log-LogFormat.cppm"
	"Source/Public/Log/Log-LogHelper.cppm"
	"Source/Public/Log/Log-LogInput.cppm"
	"Source/Public/Log/Log-LogType.cppm"
	"Source/Public/Platform/Platform.cppm"
	"Source/Public/Utility/Utility.cppm"
	"Source/Public/Utility/Utility-SafeFormat.cppm"
)

if(PONY_WINCORE)
	message(VERBOSE "Configuring headers for WinCore")
	target_include_directories(PonyEngine.Core PUBLIC 
		"Include/Public/WinCore"
	)

	message(VERBOSE "Configuring sources for WinCore")
	target_sources(PonyEngine.Core PUBLIC FILE_SET CXX_MODULES FILES
		"Source/Public/Platform/WinCore/Platform.WinCore.cppm"
		"Source/Public/Platform/WinCore/Platform.WinCore-GUID.cppm"
		"Source/Public/Platform/WinCore/Platform.WinCore-Utility.cppm"
	)
endif()

if(PONY_WINDOWS)
	message(VERBOSE "Configuring headers for Windows")
	target_include_directories(PonyEngine.Core PUBLIC 
		"Include/Public/Windows"
	)

	message(VERBOSE "Configuring sources for Windows")
	target_sources(PonyEngine.Core PUBLIC FILE_SET CXX_MODULES FILES
		"Source/Public/Platform/Windows/Platform.Windows.cppm"
		"Source/Public/Platform/Windows/Platform.Windows-Cursor.cppm"
		"Source/Public/Platform/Windows/Platform.Windows-Module.cppm"
	)
endif()

message(VERBOSE "Configuring defines")
if(PONY_WINCORE)
	target_compile_definitions(PonyEngine.Core PUBLIC PONY_WINCORE)
endif()
if(PONY_WINDOWS)
	target_compile_definitions(PonyEngine.Core PUBLIC PONY_WINDOWS)
endif()

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Core PROPERTIES CXX_STANDARD 23)
set_target_properties(PonyEngine.Core PROPERTIES OUTPUT_NAME "PonyEngine.Core.API")
