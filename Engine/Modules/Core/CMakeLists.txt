message(STATUS "Configuring PonyEngine.Core")

include("CMake/Target.cmake")

add_library(PonyEngine.Core STATIC)

target_include_directories(PonyEngine.Core PUBLIC 
	"Include/Public"
)

target_sources(PonyEngine.Core PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Async.cppm"
	"Source/Async-IRequest.cppm"
	"Source/Async-RequestStatus.cppm"
	"Source/Chrono.cppm"
	"Source/Chrono-Conversion.cppm"
	"Source/Container.cppm"
	"Source/Container-AlignedAllocator.cppm"
	"Source/Format.cppm"
	"Source/Format-Optional.cppm"
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
	"Source/Memory-Utility.cppm"
	"Source/Meta.cppm"
	"Source/Meta-Version.cppm"
	"Source/Utility.cppm"
	"Source/Utility-Concepts.cppm"
	"Source/Utility-Overload.cppm"
)

set_target_properties(PonyEngine.Core PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)
