message(STATUS "Configuring PonyEngine.Config")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Config STATIC)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Config PUBLIC FILE_SET CXX_MODULES FILES 
	"Source/Public/Config/Config.cppm"
	"Source/Public/Config/Config-Constants.cppm"
	"Source/Public/Config/Config-IConfigService.cppm"
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Config PROPERTIES 
	CXX_STANDARD 23
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Config PUBLIC
	PonyEngine.Core
)
