message(STATUS "Configuring PonyEngine.Math")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Math STATIC)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Math PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Public/Math/Math.cppm"
	"Source/Public/Math/Math-Ball.cppm"
	"Source/Public/Math/Math-Color.cppm"
	"Source/Public/Math/Math-Common.cppm"
	"Source/Public/Math/Math-InternalUtility.cppm"
	"Source/Public/Math/Math-Matrix.cppm"
	"Source/Public/Math/Math-Quaternion.cppm"
	"Source/Public/Math/Math-Transformations.cppm"
	"Source/Public/Math/Math-Transform.cppm"
	"Source/Public/Math/Math-Vector.cppm"
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Math PROPERTIES 
	CXX_STANDARD 23
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Math PUBLIC
	PonyEngine.Core
)
