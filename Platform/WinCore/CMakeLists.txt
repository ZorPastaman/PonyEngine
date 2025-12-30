add_subdirectory("Core")

if(TARGET PonyEngine.RenderDevice.D3D12.Impl)
	add_subdirectory("RenderDevice.D3D12.Impl")
endif()
