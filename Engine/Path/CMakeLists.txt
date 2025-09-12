message(STATUS "Configuring PonyEngine.Path")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Path STATIC)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Path PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Public/Path/Path.cppm"
	"Source/Public/Path/Path-IPathService.cppm"
	"Source/Public/Path/Path-PathIds.cppm"
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Path PROPERTIES 
	CXX_STANDARD 23
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Path PUBLIC
	PonyEngine.Core
)
