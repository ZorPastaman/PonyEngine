message(STATUS "Configuring PonyEngine.RenderDevice")

message(VERBOSE "Configuring target")
add_library(PonyEngine.RenderDevice STATIC)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.RenderDevice PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Public/RenderDevice.cppm"
	"Source/Public/RenderDevice-IRenderDeviceService.cppm"	
	"Source/Public/RenderDevice-RenderAPI.cppm" 
	"Source/Public/RenderDevice-SampleCount.cppm"
	"Source/Public/RenderDevice-TextureCreateInfo.cppm"
	"Source/Public/RenderDevice-TextureDimension.cppm"
	"Source/Public/RenderDevice-TextureFormat.cppm"
	"Source/Public/RenderDevice-TextureFormatFeature.cppm"
	"Source/Public/RenderDevice-TextureFormatId.cppm"
	"Source/Public/RenderDevice-TextureSupportRequest.cppm"
	"Source/Public/RenderDevice-TextureSupportResponse.cppm"
	"Source/Public/RenderDevice-TextureUsage.cppm"
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
