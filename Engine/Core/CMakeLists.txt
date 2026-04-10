message(STATUS "Configuring PonyEngine.Core")

message(VERBOSE "Configuring environment")
include("CMake/Target.cmake")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Core STATIC)

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.Core PUBLIC 
	"Include/Public"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Core PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Hash.cppm"
	"Source/Hash-FNV1a.cppm"
	"Source/Math.cppm"
	"Source/Math-Ball.cppm"
	"Source/Math-Bounds.cppm"
	"Source/Math-Box.cppm"
	"Source/Math-Color.cppm"
	"Source/Math-Common.cppm"
	"Source/Math-CornerBox.cppm"
	"Source/Math-Flat.cppm"
	"Source/Math-Insides.cppm"
	"Source/Math-InternalUtility.cppm"
	"Source/Math-Intersections.cppm"
	"Source/Math-Matrix.cppm"
	"Source/Math-OrientedBox.cppm"
	"Source/Math-Quaternion.cppm"
	"Source/Math-Ray.cppm"
	"Source/Math-Transformations.cppm"
	"Source/Math-Transform.cppm"
	"Source/Math-Vector.cppm"
	"Source/Memory.cppm"
	"Source/Memory-Arena.cppm"
	"Source/Memory-Pool.cppm"
	"Source/Meta.cppm"
	"Source/Meta-Version.cppm"
	"Source/Serialization.cppm"
	"Source/Serialization-Array.cppm"
	"Source/Serialization-Basic.cppm"
	"Source/Type.cppm"
	"Source/Type-Common.cppm"
	"Source/Type-Limits.cppm"
	"Source/Type-Variant.cppm"
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Core PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)
