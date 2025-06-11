message(STATUS "Configuring PonyEngine.Core")
add_library(PonyEngine.Core STATIC)

message(STATUS "Configuring headers")
target_include_directories(PonyEngine.Core PUBLIC 
	"Include/Public/Common"
)

message(STATUS "Configuring sources")
target_sources(PonyEngine.Core PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Public/Core/Core.cppm"
	"Source/Public/Core/Core-IApplicationContext.cppm"
	"Source/Public/Core/Core-IEngine.cppm"
	"Source/Public/Core/Core-ILoggerFactory.cppm"
	"Source/Public/Core/Core-IModule.cppm"
	"Source/Public/Core/Core-IModuleContext.cppm"
	"Source/Public/Log/Log.cppm"
	"Source/Public/Log/Log-ILogger.cppm"
	"Source/Public/Log/Log-LogFormat.cppm"
	"Source/Public/Log/Log-LogHelper.cppm"
	"Source/Public/Log/Log-LogInput.cppm"
	"Source/Public/Log/Log-LogType.cppm"
	"Source/Public/Platform/Platform.cppm"
	"Source/Public/Utility/Utility.cppm"
	"Source/Public/Utility/Utility-SafeFormat.cppm"
)

if(PONY_WINCORE)
	message(STATUS "Configuring headers for WinCore")
	target_include_directories(PonyEngine.Core PUBLIC 
		"Include/Public/WinCore"
	)

	message(STATUS "Configuring sources for WinCore")
	target_sources(PonyEngine.Core PUBLIC FILE_SET CXX_MODULES FILES
		"Source/Public/Platform/WinCore/Platform.WinCore.cppm"
		"Source/Public/Platform/WinCore/Platform.WinCore-GUID.cppm"
		"Source/Public/Platform/WinCore/Platform.WinCore-Utility.cppm"
	)
endif()

if(PONY_WINDOWS)
	message(STATUS "Configuring headers for Windows")
	target_include_directories(PonyEngine.Core PUBLIC 
		"Include/Public/Windows"
	)

	message(STATUS "Configuring sources for Windows")
	target_sources(PonyEngine.Core PUBLIC FILE_SET CXX_MODULES FILES
		"Source/Public/Platform/Windows/Platform.Windows.cppm"
		"Source/Public/Platform/Windows/Platform.Windows-Cursor.cppm"
		"Source/Public/Platform/Windows/Platform.Windows-Module.cppm"
	)
endif()

message(STATUS "Configuring defines")
pony_set_log_mask(PonyEngine.Core TRUE)

message(STATUS "Setting properties")
set_target_properties(PonyEngine.Core PROPERTIES OUTPUT_NAME "PonyEngine.Core.API")

message(STATUS "Setting build options")
pony_set_build_options(PonyEngine.Core TRUE)
set_target_properties(PonyEngine.Core PROPERTIES CXX_STANDARD 23)
