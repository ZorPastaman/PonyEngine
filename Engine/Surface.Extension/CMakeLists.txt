message(STATUS "Configuring PonyEngine.Surface.Extension")

message(VERBOSE "Validating settings")
if(NOT TARGET PonyEngine.Surface)
	message(FATAL_ERROR "PonyEngine.Surface wasn't configured")
endif()

message(VERBOSE "Configuring target")
add_library(PonyEngine.Surface.Extension STATIC)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Surface.Extension PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Public/Surface.Extension/Surface.Extension.cppm"
	"Source/Public/Surface.Extension/Surface.Extension-SurfaceParams.cppm"
)

if(PONY_WINDOWS)
	message(VERBOSE "Configuring sources for Windows")
	target_sources(PonyEngine.Surface.Extension PUBLIC FILE_SET CXX_MODULES FILES
		"Source/Public/Surface.Extension/Windows/Surface.Extension.Windows.cppm"
		"Source/Public/Surface.Extension/Windows/Surface.Extension.Windows-SurfaceParams.cppm"
	)
endif()

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Surface.Extension PROPERTIES 
	CXX_STANDARD 23
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Surface.Extension PUBLIC
	PonyEngine.Core
	PonyEngine.Surface
)
