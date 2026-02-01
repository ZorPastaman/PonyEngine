message(STATUS "Configuring PonyEngine.RenderDevice.D3D12.Impl for Windows")

message(VERBOSE "Configuring parameters")
set(PONY_ENGINE_RENDER_DEVICE_D3D12_ORDER "p" CACHE STRING "PonyEngine.RenderDevice.D3D12.Impl module initialization order. Its first character must be in range [b-y].")


message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.RenderDevice.D3D12.Impl PUBLIC
	"Include/Public"
)
message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.RenderDevice.D3D12.Impl PRIVATE
	"Include/Private"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.RenderDevice.D3D12.Impl PUBLIC
	"Source/Main.cpp"
)
target_sources(PonyEngine.RenderDevice.D3D12.Impl PRIVATE
	"Source/Main.Impl.cpp"
)
target_sources(PonyEngine.RenderDevice.D3D12.Impl PUBLIC FILE_SET CXX_MODULES BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}" FILES
	"Source/Private/Main.cppm"
	"Source/Private/Main-DXGIFactory.cppm"
	"Source/Private/Main-DXGISwapChain.cppm"
	"Source/Private/Main-DXGISwapChainUtility.cppm"
	"Source/Private/Main-D3D12Backend.cppm"
	"Source/Private/Main-D3D12BackendModule.cppm"
	"Source/Private/Main-D3D12Buffer.cppm"
	"Source/Private/Main-D3D12BufferUtility.cppm"
	"Source/Private/Main-D3D12BundleCommandList.cppm"
	"Source/Private/Main-D3D12CommandList.cppm"
	"Source/Private/Main-D3D12CommandQueue.cppm"
	"Source/Private/Main-D3D12ComputeCommandList.cppm"
	"Source/Private/Main-D3D12CopyCommandList.cppm"
	"Source/Private/Main-D3D12DepthStencilContainer.cppm"
	"Source/Private/Main-D3D12DescriptorHeap.cppm"
	"Source/Private/Main-D3D12DescriptorHeapUtility.cppm"
	"Source/Private/Main-D3D12Device.cppm"
	"Source/Private/Main-D3D12Engine.cppm"
	"Source/Private/Main-D3D12Fence.cppm"
	"Source/Private/Main-D3D12FormatUtility.cppm"
	"Source/Private/Main-D3D12GraphicsCommandList.cppm"
	"Source/Private/Main-D3D12HeapUtility.cppm"
	"Source/Private/Main-D3D12ObjectUtility.cppm"
	"Source/Private/Main-D3D12RenderTargetContainer.cppm"
	"Source/Private/Main-D3D12Resource.cppm"
	"Source/Private/Main-D3D12RootSignature.cppm"
	"Source/Private/Main-D3D12RootSignatureUtility.cppm"
	"Source/Private/Main-D3D12SamplerContainer.cppm"
	"Source/Private/Main-D3D12SamplerUtility.cppm"
	"Source/Private/Main-D3D12ShaderDataContainer.cppm"
	"Source/Private/Main-D3D12SwapChain.cppm"
	"Source/Private/Main-D3D12Texture.cppm"
	"Source/Private/Main-D3D12TextureFormatMap.cppm"
	"Source/Private/Main-D3D12TextureUtility.cppm"
	"Source/Private/Main-D3D12Utility.cppm"
	"Source/Private/Main-D3D12Waiter.cppm"
)

message(VERBOSE "Configuring defines")
pony_validate_module_order(PONY_ENGINE_RENDER_DEVICE_D3D12_ORDER)
target_compile_definitions(PonyEngine.RenderDevice.D3D12.Impl PUBLIC
	PONY_ENGINE_RENDER_DEVICE_D3D12_ORDER=${PONY_ENGINE_RENDER_DEVICE_D3D12_ORDER}
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
target_link_libraries(PonyEngine.RenderDevice.D3D12.Impl PUBLIC
	PonyEngine.Application.Ext
)
target_link_libraries(PonyEngine.RenderDevice.D3D12.Impl PRIVATE
	PonyEngine.RenderDevice
	PonyEngine.RenderDevice.Ext
	PonyEngine.Core
	PonyEngine.Log
	PonyEngine.Surface
)
target_link_libraries(PonyEngine.RenderDevice.D3D12.Impl PRIVATE
	d3d12.lib
	dxgi.lib
	dxguid.lib
)
