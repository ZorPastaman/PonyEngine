message(STATUS "Configuring PonyEngine.Core")

message(VERBOSE "Configuring environment")
include("CMake/Log.cmake")
include("CMake/Target.cmake")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Core STATIC)

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.Core PUBLIC 
	"Include/Public/Common"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Core PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Public/File/File.cppm"
	"Source/Public/File/File-Module.cppm"
	"Source/Public/File/File-Path.cppm"
	"Source/Public/ID/ID.cppm"
	"Source/Public/ID/ID-WinGUID.cppm"
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
endif()

if(PONY_WINDOWS)
	message(VERBOSE "Configuring headers for Windows")
	target_include_directories(PonyEngine.Core PUBLIC 
		"Include/Public/Windows"
	)
endif()

message(VERBOSE "Configuring defines")
target_compile_definitions(PonyEngine.Core PUBLIC
	$<$<BOOL:${PONY_WINCORE}>:PONY_WINCORE>
	$<$<BOOL:${PONY_WINDOWS}>:PONY_WINDOWS>
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Core PROPERTIES 
	CXX_STANDARD 23
	POSITION_INDEPENDENT_CODE TRUE
)
