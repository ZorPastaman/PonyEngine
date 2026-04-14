message(STATUS "Configuring PonyEngine.Surface")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Surface STATIC)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Surface PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Main.cppm"
	"Source/Main-ISurfaceObserver.cppm"
	"Source/Main-ISurfaceService.cppm"
	"Source/Main-MathUtility.cppm"
	"Source/Main-RectStyle.cppm"
	"Source/Main-SurfaceFeature.cppm"
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
