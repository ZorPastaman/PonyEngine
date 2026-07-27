message(STATUS "Configuring PonyEngine.RenderDevice.D3D12.Impl")

message(VERBOSE "Configuring target")
add_library(PonyEngine.RenderDevice.D3D12.Impl STATIC)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.RenderDevice.D3D12.Impl PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
if(NOT TARGET PonyEngine.RenderDevice)
	message(FATAL_ERROR "PonyEngine.RenderDevice wasn't configured")
endif()
if(NOT TARGET PonyEngine.RenderDevice.Ext)
	message(FATAL_ERROR "PonyEngine.RenderDevice.Ext wasn't configured")
endif()
target_link_libraries(PonyEngine.RenderDevice.D3D12.Impl PRIVATE
	PonyEngine.RenderDevice
	PonyEngine.RenderDevice.Ext
)
