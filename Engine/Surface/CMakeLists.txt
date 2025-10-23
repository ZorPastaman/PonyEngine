message(STATUS "Configuring PonyEngine.Surface")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Surface STATIC)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Surface PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Public/Surface.cppm"
	"Source/Public/Surface-IRawInputObserver.cppm"
	"Source/Public/Surface-ISurfaceObserver.cppm"
	"Source/Public/Surface-ISurfaceService.cppm"
	"Source/Public/Surface-RectStyle.cppm"
	"Source/Public/Surface-Utility.cppm"
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Surface PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Surface PRIVATE
	PonyEngine.Core
)
