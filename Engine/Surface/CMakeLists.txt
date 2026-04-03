message(STATUS "Configuring PonyEngine.Surface")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Surface STATIC)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Surface PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Public/Main.cppm"
	"Source/Public/Main-ISurfaceObserver.cppm"
	"Source/Public/Main-ISurfaceService.cppm"
	"Source/Public/Main-MathUtility.cppm"
	"Source/Public/Main-RectStyle.cppm"
	"Source/Public/Main-SurfaceFeature.cppm"
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Surface PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Surface PUBLIC
	PonyEngine.Core
)
