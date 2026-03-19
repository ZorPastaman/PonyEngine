message(STATUS "Configuring PonyEngine.RenderDevice.Ext")

message(VERBOSE "Configuring target")
add_library(PonyEngine.RenderDevice.Ext STATIC)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.RenderDevice.Ext PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Public/Main.cppm"
	"Source/Public/Main-BackendHandle.cppm"
	"Source/Public/Main-IBackend.cppm"
	"Source/Public/Main-IRenderDeviceContext.cppm"
	"Source/Public/Main-IRenderDeviceModuleContext.cppm"
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.RenderDevice.Ext PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.RenderDevice.Ext PUBLIC
	PonyEngine.RenderDevice
	PonyEngine.Core
	PonyEngine.Application.Ext
	PonyEngine.Log
)
