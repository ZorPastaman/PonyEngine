message(STATUS "Configuring PonyEngine.RenderDevice")

message(VERBOSE "Configuring target")
add_library(PonyEngine.RenderDevice STATIC)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.RenderDevice PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Public/RenderDevice.cppm"
	"Source/Public/RenderDevice-BufferParams.cppm"
	"Source/Public/RenderDevice-BufferUsage.cppm"
	"Source/Public/RenderDevice-ClearValue.cppm"
	"Source/Public/RenderDevice-DepthStencil.cppm"
	"Source/Public/RenderDevice-HeapType.cppm"
	"Source/Public/RenderDevice-IBuffer.cppm"
	"Source/Public/RenderDevice-IComputeCommandQueue.cppm"
	"Source/Public/RenderDevice-ICopyCommandQueue.cppm"
	"Source/Public/RenderDevice-IGraphicsCommandQueue.cppm"
	"Source/Public/RenderDevice-IRenderDeviceService.cppm"
	"Source/Public/RenderDevice-ITexture.cppm"
	"Source/Public/RenderDevice-Layout.cppm"
	"Source/Public/RenderDevice-RenderAPI.cppm" 
	"Source/Public/RenderDevice-SampleCount.cppm"
	"Source/Public/RenderDevice-TextureDimension.cppm"
	"Source/Public/RenderDevice-TextureFlag.cppm"
	"Source/Public/RenderDevice-TextureFormat.cppm"
	"Source/Public/RenderDevice-TextureFormatFeature.cppm"
	"Source/Public/RenderDevice-TextureFormatId.cppm"
	"Source/Public/RenderDevice-TextureParams.cppm"
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
