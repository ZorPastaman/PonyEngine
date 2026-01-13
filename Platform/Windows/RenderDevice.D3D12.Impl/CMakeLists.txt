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
	"Source/Main.Windows.cpp"
)
target_sources(PonyEngine.RenderDevice.D3D12.Impl PRIVATE
	"Source/Main.Impl.Windows.cpp"
)
target_sources(PonyEngine.RenderDevice.D3D12.Impl PUBLIC FILE_SET CXX_MODULES BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}" FILES
	"Source/Private/RenderDevice.D3D12.Impl.Windows.cppm"
	"Source/Private/RenderDevice.D3D12.Impl.Windows-DXGIFactory.cppm"
	"Source/Private/RenderDevice.D3D12.Impl.Windows-DXGISwapChain.cppm"
	"Source/Private/RenderDevice.D3D12.Impl.Windows-DXGITextureFormatMap.cppm"
	"Source/Private/RenderDevice.D3D12.Impl.Windows-D3D12Backend.cppm"
	"Source/Private/RenderDevice.D3D12.Impl.Windows-D3D12BackendModule.cppm"
	"Source/Private/RenderDevice.D3D12.Impl.Windows-D3D12Buffer.cppm"
	"Source/Private/RenderDevice.D3D12.Impl.Windows-D3D12CommandQueue.cppm"
	"Source/Private/RenderDevice.D3D12.Impl.Windows-D3D12ComputeCommandQueue.cppm"
	"Source/Private/RenderDevice.D3D12.Impl.Windows-D3D12CopyCommandQueue.cppm"
	"Source/Private/RenderDevice.D3D12.Impl.Windows-D3D12Device.cppm"
	"Source/Private/RenderDevice.D3D12.Impl.Windows-D3D12Engine.cppm"
	"Source/Private/RenderDevice.D3D12.Impl.Windows-D3D12GraphicsCommandQueue.cppm"
	"Source/Private/RenderDevice.D3D12.Impl.Windows-D3D12Texture.cppm"
	"Source/Private/RenderDevice.D3D12.Impl.Windows-D3D12Utility.cppm"
	"Source/Private/RenderDevice.D3D12.Impl.Windows-EngineUtility.cppm"
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
