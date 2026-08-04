message(STATUS "Configuring PonyEngine.RenderDevice.Impl")

set(PONY_ENGINE_RENDER_DEVICE_ORDER "p" CACHE STRING "PonyEngine.RenderDevice.Impl module initialization order. Its first character must be in range [b-y].")

add_library(PonyEngine.RenderDevice.Impl STATIC)

target_include_directories(PonyEngine.RenderDevice.Impl PUBLIC
	"Include/Public"
)

target_sources(PonyEngine.RenderDevice.Impl PUBLIC
	"Source/Launch.cpp"
)
target_sources(PonyEngine.RenderDevice.Impl PRIVATE
	"Source/Launch.Impl.cpp"
)
target_sources(PonyEngine.RenderDevice.Impl PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Main.cppm"
	"Source/Main-BackendContainer.cppm"
	"Source/Main-RenderDeviceService.cppm"
	"Source/Main-RenderDeviceServiceModule.cppm"
)

pony_validate_module_order(PONY_ENGINE_RENDER_DEVICE_ORDER)
target_compile_definitions(PonyEngine.RenderDevice.Impl PUBLIC
	PONY_ENGINE_RENDER_DEVICE_ORDER=${PONY_ENGINE_RENDER_DEVICE_ORDER}
)

set_target_properties(PonyEngine.RenderDevice.Impl PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

if(NOT TARGET PonyEngine.RenderDevice)
	message(FATAL_ERROR "PonyEngine.RenderDevice wasn't configured")
endif()
if(NOT TARGET PonyEngine.RenderDevice.Ext)
	message(FATAL_ERROR "PonyEngine.RenderDevice.Ext wasn't configured")
endif()
target_link_libraries(PonyEngine.RenderDevice.Impl PUBLIC
	PonyEngine.Application
)
target_link_libraries(PonyEngine.RenderDevice.Impl PRIVATE
	PonyEngine.RenderDevice
	PonyEngine.RenderDevice.Ext
	PonyEngine.Core
	PonyEngine.Log
)
