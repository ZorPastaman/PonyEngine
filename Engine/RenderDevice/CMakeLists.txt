message(STATUS "Configuring PonyEngine.RenderDevice")

message(VERBOSE "Configuring target")
add_library(PonyEngine.RenderDevice STATIC)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.RenderDevice PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Public/Main.cppm"
	"Source/Public/Main-Aspect.cppm"
	"Source/Public/Main-BufferParams.cppm"
	"Source/Public/Main-BufferUsage.cppm"
	"Source/Public/Main-CBVParams.cppm"
	"Source/Public/Main-CBVRequirement.cppm"
	"Source/Public/Main-ClearValue.cppm"
	"Source/Public/Main-ComparisonFunc.cppm"
	"Source/Public/Main-ComponentMapping.cppm"
	"Source/Public/Main-ComponentSwizzle.cppm"
	"Source/Public/Main-CopyableFootprint.cppm"
	"Source/Public/Main-CopyableFootprintSize.cppm"
	"Source/Public/Main-DepthStencil.cppm"
	"Source/Public/Main-DepthStencilContainerParams.cppm"
	"Source/Public/Main-DepthStencilMeta.cppm"
	"Source/Public/Main-DeviceSupport.cppm"
	"Source/Public/Main-DSVDimension.cppm"
	"Source/Public/Main-DSVFlag.cppm"
	"Source/Public/Main-DSVLayout.cppm"
	"Source/Public/Main-DSVParams.cppm"
	"Source/Public/Main-FenceValue.cppm"
	"Source/Public/Main-Filter.cppm"
	"Source/Public/Main-HeapType.cppm"
	"Source/Public/Main-IBuffer.cppm"
	"Source/Public/Main-ICommandList.cppm"
	"Source/Public/Main-IComputeCommandList.cppm"
	"Source/Public/Main-ICopyCommandList.cppm"
	"Source/Public/Main-IDepthStencilContainer.cppm"
	"Source/Public/Main-IFence.cppm"
	"Source/Public/Main-IGraphicsCommandList.cppm"
	"Source/Public/Main-IRenderDeviceService.cppm"
	"Source/Public/Main-IRenderTargetContainer.cppm"
	"Source/Public/Main-IResource.cppm"
	"Source/Public/Main-ISamplerContainer.cppm"
	"Source/Public/Main-ISecondaryGraphicsCommandList.cppm"
	"Source/Public/Main-IShaderDataContainer.cppm"
	"Source/Public/Main-ITexture.cppm"
	"Source/Public/Main-IWaiter.cppm"
	"Source/Public/Main-Layout.cppm"
	"Source/Public/Main-QueueSync.cppm"
	"Source/Public/Main-Reduction.cppm"
	"Source/Public/Main-RenderAPI.cppm"
	"Source/Public/Main-RenderTargetContainerParams.cppm"
	"Source/Public/Main-RenderTargetMeta.cppm"
	"Source/Public/Main-RTVLayout.cppm"
	"Source/Public/Main-RTVParams.cppm"
	"Source/Public/Main-SampleCount.cppm"
	"Source/Public/Main-SamplerAddressMode.cppm"
	"Source/Public/Main-SamplerContainerParams.cppm"
	"Source/Public/Main-SamplerFilter.cppm"
	"Source/Public/Main-SamplerParams.cppm"
	"Source/Public/Main-SamplerSupport.cppm"
	"Source/Public/Main-ShaderDataContainerParams.cppm"
	"Source/Public/Main-ShaderDataMeta.cppm"
	"Source/Public/Main-SRVLayout.cppm"
	"Source/Public/Main-SRVParams.cppm"
	"Source/Public/Main-SubTextureIndex.cppm"
	"Source/Public/Main-SubTextureRange.cppm"
	"Source/Public/Main-SwapChainAlphaMode.cppm"
	"Source/Public/Main-SwapChainEffect.cppm"
	"Source/Public/Main-SwapChainFlag.cppm"
	"Source/Public/Main-SwapChainParams.cppm"
	"Source/Public/Main-SwapChainScaling.cppm"
	"Source/Public/Main-SwapChainSupport.cppm"
	"Source/Public/Main-SwapChainSync.cppm"
	"Source/Public/Main-TextureDimension.cppm"
	"Source/Public/Main-TextureFlag.cppm"
	"Source/Public/Main-TextureFormat.cppm"
	"Source/Public/Main-TextureFormatFeature.cppm"
	"Source/Public/Main-TextureFormatId.cppm"
	"Source/Public/Main-TextureFormatSupport.cppm"
	"Source/Public/Main-TextureParams.cppm"
	"Source/Public/Main-TextureSupportRequest.cppm"
	"Source/Public/Main-TextureSupportResponse.cppm"
	"Source/Public/Main-TextureUsage.cppm"
	"Source/Public/Main-TextureViewDimension.cppm"
	"Source/Public/Main-UAVLayout.cppm"
	"Source/Public/Main-UAVParams.cppm"
	"Source/Public/Main-Utility.cppm"
	"Source/Public/Main-ViewContainerCopyRange.cppm"
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
