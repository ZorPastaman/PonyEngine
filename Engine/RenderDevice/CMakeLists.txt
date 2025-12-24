message(STATUS "Configuring PonyEngine.RenderDevice")

message(VERBOSE "Configuring target")
add_library(PonyEngine.RenderDevice STATIC)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.RenderDevice PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Public/RenderDevice.cppm"
	"Source/Public/RenderDevice-IRenderAPI.cppm"
	"Source/Public/RenderDevice-IRenderDeviceService.cppm"	
	"Source/Public/RenderDevice-RenderAPI.cppm" 
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.RenderDevice PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.RenderDevice PUBLIC
	PonyEngine.Core
)
