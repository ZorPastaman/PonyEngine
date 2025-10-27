message(STATUS "Configuring PonyEngine.Core")

message(VERBOSE "Configuring environment")
include("CMake/Target.cmake")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Core STATIC)

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.Core PUBLIC 
	"Include/Public/Common"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Core PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Public/File.cppm"
	"Source/Public/File-Module.cppm"
	"Source/Public/File-Path.cppm"
	"Source/Public/Hash.cppm"
	"Source/Public/Hash-FNV1a.cppm"
	"Source/Public/ID.cppm"
	"Source/Public/ID-WinGUID.cppm"
	"Source/Public/Math.cppm"
	"Source/Public/Math-Ball.cppm"
	"Source/Public/Math-Bounds.cppm"
	"Source/Public/Math-Box.cppm"
	"Source/Public/Math-Color.cppm"
	"Source/Public/Math-Common.cppm"
	"Source/Public/Math-CornerBox.cppm"
	"Source/Public/Math-Flat.cppm"
	"Source/Public/Math-Insides.cppm"
	"Source/Public/Math-InternalUtility.cppm"
	"Source/Public/Math-Intersections.cppm"
	"Source/Public/Math-Matrix.cppm"
	"Source/Public/Math-OrientedBox.cppm"
	"Source/Public/Math-Quaternion.cppm"
	"Source/Public/Math-Ray.cppm"
	"Source/Public/Math-Transformations.cppm"
	"Source/Public/Math-Transform.cppm"
	"Source/Public/Math-Vector.cppm"
	"Source/Public/Serialization.cppm"
	"Source/Public/Serialization-Array.cppm"
	"Source/Public/Serialization-Basic.cppm"
	"Source/Public/Text.cppm"
	"Source/Public/Text-Convert.cppm"
	"Source/Public/Text-Format.cppm"
	"Source/Public/Type.cppm"
	"Source/Public/Type-Common.cppm"
	"Source/Public/Type-Limits.cppm"
	"Source/Public/Type-Variant.cppm"
)

if(PONY_WINDOWS)
	message(VERBOSE "Configuring headers for Windows")
	target_include_directories(PonyEngine.Core PUBLIC 
		"Include/Public/Windows"
	)
endif()

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Core PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring defines")
target_compile_definitions(PonyEngine.Core PUBLIC
	$<$<BOOL:${PONY_WINDOWS}>:PONY_WINDOWS>
)
