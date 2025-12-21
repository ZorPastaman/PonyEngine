message(STATUS "Configuring PonyEngine.Surface.Impl")

message(VERBOSE "Configuring parameters")
set(PONY_ENGINE_SURFACE_ORDER "p" CACHE STRING "PonyEngine.Surface.Impl module initialization order. Its first character must be in range [b-y].")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Surface.Impl STATIC)

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.Surface.Impl PUBLIC
	"Include/Public/Common"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Surface.Impl PUBLIC
	"Source/Main.cpp"
)
target_sources(PonyEngine.Surface.Impl PRIVATE
	"Source/Main.Impl.cpp"
)
target_sources(PonyEngine.Surface.Impl PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Private/Surface.Impl.cppm"
	"Source/Private/Surface.Impl-MemoryManager.cppm"
)

if(PONY_WINDOWS)
	message(VERBOSE "Configuring sources for Windows")
	target_sources(PonyEngine.Surface.Impl PRIVATE FILE_SET CXX_MODULES FILES 
		"Source/Private/Surface.Impl-Windows.MessageHandler.cppm"
		"Source/Private/Surface.Impl-Windows.RawInputDeviceContainer.cppm"
		"Source/Private/Surface.Impl-Windows.RawInputManager.cppm"
		"Source/Private/Surface.Impl-Windows.SurfaceService.cppm"
		"Source/Private/Surface.Impl-Windows.SurfaceServiceModule.cppm"
		"Source/Private/Surface.Impl-Windows.WindowClass.cppm"
)
endif()

message(VERBOSE "Configuring defines")
pony_validate_module_order(PONY_ENGINE_SURFACE_ORDER)
target_compile_definitions(PonyEngine.Surface.Impl PUBLIC
	PONY_ENGINE_SURFACE_ORDER=${PONY_ENGINE_SURFACE_ORDER}
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Surface.Impl PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
if(NOT TARGET PonyEngine.Surface)
	message(FATAL_ERROR "PonyEngine.Surface wasn't configured")
endif()
target_link_libraries(PonyEngine.Surface.Impl PUBLIC
	PonyEngine.Application.Ext
)
target_link_libraries(PonyEngine.Surface.Impl PRIVATE
	PonyEngine.Surface
	PonyEngine.Core
	PonyEngine.Log
	PonyEngine.MessagePump
)
