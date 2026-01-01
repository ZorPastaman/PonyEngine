message(STATUS "Configuring PonyEngine.RenderDevice.D3D12.Impl for Windows")

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.RenderDevice.D3D12.Impl PUBLIC
	"Include/Public"
)
message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.RenderDevice.D3D12.Impl PRIVATE
	"Include/Private"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.RenderDevice.D3D12.Impl PUBLIC FILE_SET CXX_MODULES BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}" FILES
	"Source/Private/RenderDevice.D3D12.Impl.Windows.cppm"
	"Source/Private/RenderDevice.D3D12.Impl.Windows-D3D12Backend.cppm"
	"Source/Private/RenderDevice.D3D12.Impl.Windows-D3D12BackendModule.cppm"
	"Source/Private/RenderDevice.D3D12.Impl.Windows-D3D12Device.cppm"
	"Source/Private/RenderDevice.D3D12.Impl.Windows-Utility.cppm"
)

message(VERBOSE "Configuring dependencies")
if(NOT TARGET PonyEngine.RenderDevice)
	message(FATAL_ERROR "PonyEngine.RenderDevice wasn't configured")
endif()
if(NOT TARGET PonyEngine.RenderDevice.Ext)
	message(FATAL_ERROR "PonyEngine.RenderDevice.Ext wasn't configured")
endif()
target_link_libraries(PonyEngine.RenderDevice.D3D12.Impl PUBLIC
	PonyEngine.Application.Ext
)
target_link_libraries(PonyEngine.RenderDevice.D3D12.Impl PRIVATE
	PonyEngine.RenderDevice
	PonyEngine.RenderDevice.Ext
	PonyEngine.Core
	PonyEngine.Log
)
target_link_libraries(PonyEngine.RenderDevice.D3D12.Impl PRIVATE
	d3d12.lib
	dxgi.lib
	dxguid.lib
)
