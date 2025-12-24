message(STATUS "Configuring PonyEngine.RenderDevice.Ext")

message(VERBOSE "Configuring target")
add_library(PonyEngine.RenderDevice.Ext STATIC)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.RenderDevice.Ext PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Public/RenderDevice.Ext.cppm"
	"Source/Public/RenderDevice.Ext-BackendHandle.cppm"
	"Source/Public/RenderDevice.Ext-IBackend.cppm"
	"Source/Public/RenderDevice.Ext-IRenderDeviceContext.cppm"
	"Source/Public/RenderDevice.Ext-IRenderDeviceModuleContext.cppm"
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
