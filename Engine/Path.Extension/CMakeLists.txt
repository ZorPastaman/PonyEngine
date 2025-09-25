message(STATUS "Configuring PonyEngine.Path.Extension")

message(VERBOSE "Validating settings")
if(NOT TARGET PonyEngine.Path)
	message(FATAL_ERROR "PonyEngine.Path wasn't configured")
endif()

message(VERBOSE "Configuring target")
add_library(PonyEngine.Path.Extension STATIC)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Path.Extension PUBLIC FILE_SET CXX_MODULES FILES 
	"Source/Public/Path.Extension/Path.Extension.cppm"
	"Source/Public/Path.Extension/Path.Extension-PathParams.cppm"
)

if(PONY_WINDOWS)
	message(VERBOSE "Configuring sources for Windows")
	target_sources(PonyEngine.Path.Extension PUBLIC FILE_SET CXX_MODULES FILES
		"Source/Public/Path.Extension/Windows/Path.Extension.Windows.cppm"
	)
endif()

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Path.Extension PROPERTIES 
	CXX_STANDARD 23
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Path.Extension PUBLIC
	PonyEngine.Core
	PonyEngine.Path
)
