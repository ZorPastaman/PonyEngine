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
	"Source/Launch.cpp"
)
target_sources(PonyEngine.RenderDevice.Direct3D12.Impl PRIVATE
	"Source/Launch.Impl.cpp"
)
target_sources(PonyEngine.RenderDevice.Direct3D12.Impl PUBLIC FILE_SET CXX_MODULES BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}" FILES
	"Source/Main.cppm"
	"Source/Main-AtomicSupport.cppm"
	"Source/Main-Backend.cppm"
	"Source/Main-BackendModule.cppm"
	"Source/Main-Buffer.cppm"
	"Source/Main-BufferUtility.cppm"
	"Source/Main-BundleCommandList.cppm"
	"Source/Main-CommandList.cppm"
	"Source/Main-CommandListUtility.cppm"
	"Source/Main-CommandQueue.cppm"
	"Source/Main-ComputeCommandList.cppm"
	"Source/Main-ComputePipelineBinding.cppm"
	"Source/Main-ComputePipelineState.cppm"
	"Source/Main-ContainerBinding.cppm"
	"Source/Main-CopyCommandList.cppm"
	"Source/Main-DepthStencilContainer.cppm"
	"Source/Main-DescriptorHeap.cppm"
	"Source/Main-DescriptorHeapUtility.cppm"
	"Source/Main-Device.cppm"
	"Source/Main-Engine.cppm"
	"Source/Main-Factory.cppm"
	"Source/Main-Fence.cppm"
	"Source/Main-FenceUtility.cppm"
	"Source/Main-FormatUtility.cppm"
	"Source/Main-GraphicsCommandList.cppm"
	"Source/Main-GraphicsComputePipelineBinding.cppm"
	"Source/Main-GraphicsPipelineBinding.cppm"
	"Source/Main-GraphicsPipelineState.cppm"
	"Source/Main-HeapUtility.cppm"
	"Source/Main-ObjectUtility.cppm"
	"Source/Main-PipelineState.cppm"
	"Source/Main-PipelineStateSubobject.cppm"
	"Source/Main-PipelineStateUtility.cppm"
	"Source/Main-RenderTargetContainer.cppm"
	"Source/Main-Resource.cppm"
	"Source/Main-RootSignature.cppm"
	"Source/Main-RootSignatureUtility.cppm"
	"Source/Main-SamplerContainer.cppm"
	"Source/Main-SamplerUtility.cppm"
	"Source/Main-ShaderDataContainer.cppm"
	"Source/Main-SwapChain.cppm"
	"Source/Main-SwapChainUtility.cppm"
	"Source/Main-SwapChainWrapper.cppm"
	"Source/Main-Texture.cppm"
	"Source/Main-TextureFormatMap.cppm"
	"Source/Main-TextureUtility.cppm"
	"Source/Main-Utility.cppm"
	"Source/Main-Waiter.cppm"
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
