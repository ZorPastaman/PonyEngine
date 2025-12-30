message(STATUS "Configuring PonyEngine.RenderDevice.D3D12.Impl for Windows")

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.RenderDevice.D3D12.Impl PRIVATE
	d3d12.lib
	dxgi.lib
	dxguid.lib
)
