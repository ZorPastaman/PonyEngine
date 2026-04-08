message(STATUS "Configuring PonyEngine.RenderDevice.Direct3D12.Impl for Windows")

message(VERBOSE "Configuring parameters")
set(PONY_ENGINE_RENDER_DEVICE_DIRECT3D12_ORDER "p" CACHE STRING "PonyEngine.RenderDevice.Direct3D12.Impl module initialization order. Its first character must be in range [b-y].")

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.RenderDevice.Direct3D12.Impl PUBLIC
	"Include/Public"
)
message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.RenderDevice.Direct3D12.Impl PRIVATE
	"Include/Private"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.RenderDevice.Direct3D12.Impl PUBLIC
	"Source/Main.cpp"
)
target_sources(PonyEngine.RenderDevice.Direct3D12.Impl PRIVATE
	"Source/Main.Impl.cpp"
)
target_sources(PonyEngine.RenderDevice.Direct3D12.Impl PUBLIC FILE_SET CXX_MODULES BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}" FILES
	"Source/Private/Main.cppm"
	"Source/Private/Main-AtomicSupport.cppm"
	"Source/Private/Main-Backend.cppm"
	"Source/Private/Main-BackendModule.cppm"
	"Source/Private/Main-Buffer.cppm"
	"Source/Private/Main-BufferUtility.cppm"
	"Source/Private/Main-BundleCommandList.cppm"
	"Source/Private/Main-CommandList.cppm"
	"Source/Private/Main-CommandListUtility.cppm"
	"Source/Private/Main-CommandQueue.cppm"
	"Source/Private/Main-ComputeCommandList.cppm"
	"Source/Private/Main-ComputePipelineBinding.cppm"
	"Source/Private/Main-ComputePipelineState.cppm"
	"Source/Private/Main-ContainerBinding.cppm"
	"Source/Private/Main-CopyCommandList.cppm"
	"Source/Private/Main-DepthStencilContainer.cppm"
	"Source/Private/Main-DescriptorHeap.cppm"
	"Source/Private/Main-DescriptorHeapUtility.cppm"
	"Source/Private/Main-Device.cppm"
	"Source/Private/Main-Engine.cppm"
	"Source/Private/Main-Factory.cppm"
	"Source/Private/Main-Fence.cppm"
	"Source/Private/Main-FenceUtility.cppm"
	"Source/Private/Main-FormatUtility.cppm"
	"Source/Private/Main-GraphicsCommandList.cppm"
	"Source/Private/Main-GraphicsComputePipelineBinding.cppm"
	"Source/Private/Main-GraphicsPipelineBinding.cppm"
	"Source/Private/Main-GraphicsPipelineState.cppm"
	"Source/Private/Main-HeapUtility.cppm"
	"Source/Private/Main-ObjectUtility.cppm"
	"Source/Private/Main-PipelineState.cppm"
	"Source/Private/Main-PipelineStateSubobject.cppm"
	"Source/Private/Main-PipelineStateUtility.cppm"
	"Source/Private/Main-RenderTargetContainer.cppm"
	"Source/Private/Main-Resource.cppm"
	"Source/Private/Main-RootSignature.cppm"
	"Source/Private/Main-RootSignatureUtility.cppm"
	"Source/Private/Main-SamplerContainer.cppm"
	"Source/Private/Main-SamplerUtility.cppm"
	"Source/Private/Main-ShaderDataContainer.cppm"
	"Source/Private/Main-SwapChain.cppm"
	"Source/Private/Main-SwapChainUtility.cppm"
	"Source/Private/Main-SwapChainWrapper.cppm"
	"Source/Private/Main-Texture.cppm"
	"Source/Private/Main-TextureFormatMap.cppm"
	"Source/Private/Main-TextureUtility.cppm"
	"Source/Private/Main-Utility.cppm"
	"Source/Private/Main-Waiter.cppm"
)

message(VERBOSE "Configuring defines")
pony_validate_module_order(PONY_ENGINE_RENDER_DEVICE_DIRECT3D12_ORDER)
target_compile_definitions(PonyEngine.RenderDevice.Direct3D12.Impl PUBLIC
	PONY_ENGINE_RENDER_DEVICE_DIRECT3D12_ORDER=${PONY_ENGINE_RENDER_DEVICE_DIRECT3D12_ORDER}
)

message(VERBOSE "Configuring dependencies")
if(NOT TARGET PonyEngine.RenderDevice)
	message(FATAL_ERROR "PonyEngine.RenderDevice wasn't configured")
endif()
if(NOT TARGET PonyEngine.RenderDevice.Ext)
	message(FATAL_ERROR "PonyEngine.RenderDevice.Ext wasn't configured")
endif()
if(NOT TARGET PonyEngine.Surface)
	message(FATAL_ERROR "PonyEngine.Surface wasn't configured")
endif()
target_link_libraries(PonyEngine.RenderDevice.Direct3D12.Impl PUBLIC
	PonyEngine.Application.Ext
)
target_link_libraries(PonyEngine.RenderDevice.Direct3D12.Impl PRIVATE
	PonyEngine.Core
	PonyEngine.Log
	PonyEngine.Surface
)
target_link_libraries(PonyEngine.RenderDevice.Direct3D12.Impl PRIVATE
	d3d12.lib
	dxgi.lib
	dxguid.lib
)
