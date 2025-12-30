message(STATUS "Configuring PonyEngine.RenderDevice.D3D12.Impl for WinCore")

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.RenderDevice.D3D12.Impl PUBLIC FILE_SET CXX_MODULES BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}" FILES
	"Source/Private/RenderDevice.D3D12.Impl.WinCore.cppm"
)
