message(STATUS "Configuring PonyEngine.Math")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Math STATIC)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Math PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Public/Math/Math.cppm"
	"Source/Public/Math/Math-Common.cppm"
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Math PROPERTIES 
	CXX_STANDARD 23
	POSITION_INDEPENDENT_CODE TRUE
)
