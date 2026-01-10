message(STATUS "Configuring PonyEngine.RenderDevice.Impl")

message(VERBOSE "Configuring parameters")
set(PONY_ENGINE_RENDER_DEVICE_ORDER "p" CACHE STRING "PonyEngine.RenderDevice.Impl module initialization order. Its first character must be in range [b-y].")

message(VERBOSE "Configuring target")
add_library(PonyEngine.RenderDevice.Impl STATIC)

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.RenderDevice.Impl PUBLIC
	"Include/Public"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.RenderDevice.Impl PUBLIC
	"Source/Main.cpp"
)
target_sources(PonyEngine.RenderDevice.Impl PRIVATE
	"Source/Main.Impl.cpp"
)
target_sources(PonyEngine.RenderDevice.Impl PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Private/RenderDevice.Impl.cppm"
	"Source/Private/RenderDevice.Impl-BackendContainer.cppm"
	"Source/Private/RenderDevice.Impl-RenderDeviceService.cppm"
	"Source/Private/RenderDevice.Impl-RenderDeviceServiceModule.cppm"
)

message(VERBOSE "Configuring defines")
pony_validate_module_order(PONY_ENGINE_RENDER_DEVICE_ORDER)
target_compile_definitions(PonyEngine.RenderDevice.Impl PUBLIC
	PONY_ENGINE_RENDER_DEVICE_ORDER=${PONY_ENGINE_RENDER_DEVICE_ORDER}
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.RenderDevice.Impl PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
if(NOT TARGET PonyEngine.RenderDevice)
	message(FATAL_ERROR "PonyEngine.RenderDevice wasn't configured")
endif()
if(NOT TARGET PonyEngine.RenderDevice.Ext)
	message(FATAL_ERROR "PonyEngine.RenderDevice.Ext wasn't configured")
endif()
target_link_libraries(PonyEngine.RenderDevice.Impl PUBLIC
	PonyEngine.Application.Ext
)
target_link_libraries(PonyEngine.RenderDevice.Impl PRIVATE
	PonyEngine.RenderDevice
	PonyEngine.RenderDevice.Ext
	PonyEngine.Core
	PonyEngine.Log
)
