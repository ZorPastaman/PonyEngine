message(STATUS "Configuring PonyEngine.World")

message(VERBOSE "Configuring target")
add_library(PonyEngine.World STATIC)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.World PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Main.cppm"
	"Source/Main-Component.cppm"
	"Source/Main-Entity.cppm"
	"Source/Main-IWorld.cppm"
	"Source/Main-IWorldService.cppm"
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.World PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.World PUBLIC
	PonyEngine.Core
)
