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
	"Source/Public/Application/Application-IApplicationContext.cppm"
	"Source/Public/Application/Application-IModule.cppm"
	"Source/Public/Application/Application-IModuleContext.cppm"
	"Source/Public/Application/Application-IService.cppm"
	"Source/Public/Application/Application-IServiceFactory.cppm"
	"Source/Public/Application/Application-ITickableService.cppm"
	"Source/Public/Application/Application-ServiceData.cppm"
	"Source/Public/File/File.cppm"
	"Source/Public/File/File-Module.cppm"
	"Source/Public/File/File-Path.cppm"
	"Source/Public/ID/ID.cppm"
	"Source/Public/ID/ID-WinGUID.cppm"
	"Source/Public/Log/Log.cppm"
	"Source/Public/Log/Log-ILogger.cppm"
	"Source/Public/Log/Log-LogData.cppm"
	"Source/Public/Log/Log-LogFormat.cppm"
	"Source/Public/Log/Log-LogHelper.cppm"
	"Source/Public/Log/Log-LogType.cppm"
	"Source/Public/Math/Math.cppm"
	"Source/Public/Math/Math-Ball.cppm"
	"Source/Public/Math/Math-Bounds.cppm"
	"Source/Public/Math/Math-Box.cppm"
	"Source/Public/Math/Math-Color.cppm"
	"Source/Public/Math/Math-Common.cppm"
	"Source/Public/Math/Math-Flat.cppm"
	"Source/Public/Math/Math-Insides.cppm"
	"Source/Public/Math/Math-InternalUtility.cppm"
	"Source/Public/Math/Math-Intersections.cppm"
	"Source/Public/Math/Math-Matrix.cppm"
	"Source/Public/Math/Math-OrientedBox.cppm"
	"Source/Public/Math/Math-Quaternion.cppm"
	"Source/Public/Math/Math-Ray.cppm"
	"Source/Public/Math/Math-Transformations.cppm"
	"Source/Public/Math/Math-Transform.cppm"
	"Source/Public/Math/Math-Vector.cppm"
	"Source/Public/Memory/Memory.cppm"
	"Source/Public/Memory/Memory-Mutability.cppm"
	"Source/Public/Memory/Memory-TypedPtr.cppm"
	"Source/Public/Text/Text.cppm"
	"Source/Public/Text/Text-Convert.cppm"
	"Source/Public/Text/Text-Format.cppm"
	"Source/Public/Type/Type.cppm"
	"Source/Public/Type/Type-Common.cppm"
)

if(PONY_WINCORE)
	message(VERBOSE "Configuring headers for WinCore")
	target_include_directories(PonyEngine.Core PUBLIC 
		"Include/Public/WinCore"
	)

	message(VERBOSE "Configuring sources for WinCore")
	target_sources(PonyEngine.Core PUBLIC FILE_SET CXX_MODULES FILES
		"Source/Public/Application/WinCore/Application.WinCore.cppm"
	)
endif()

if(PONY_WINDOWS)
	message(VERBOSE "Configuring headers for Windows")
	target_include_directories(PonyEngine.Core PUBLIC 
		"Include/Public/Windows"
	)

	message(VERBOSE "Configuring sources for Windows")
	target_sources(PonyEngine.Core PUBLIC FILE_SET CXX_MODULES FILES
		"Source/Public/Application/Windows/Application.Windows.cppm"
		"Source/Public/Application/Windows/Application.Windows-IMainDataService.cppm"
		"Source/Public/Application/Windows/Application.Windows-IMessageLoopService.cppm"
		"Source/Public/Application/Windows/Application.Windows-IMessageObserver.cppm"
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
set_target_properties(PonyEngine.Core PROPERTIES 
	CXX_STANDARD 23
	POSITION_INDEPENDENT_CODE TRUE
)
