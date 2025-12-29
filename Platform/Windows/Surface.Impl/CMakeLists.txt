message(STATUS "Configuring PonyEngine.Surface.Impl for Windows")

message(VERBOSE "Configuring parameters")
set(PONY_ENGINE_SURFACE_ORDER "p" CACHE STRING "PonyEngine.Surface.Impl module initialization order. Its first character must be in range [b-y].")

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.Surface.Impl PUBLIC
	"Include/Public"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Surface.Impl PUBLIC
	"Source/Main.Windows.cpp"
)
target_sources(PonyEngine.Surface.Impl PRIVATE
	"Source/Main.Impl.Windows.cpp"
)
target_sources(PonyEngine.Surface.Impl PRIVATE FILE_SET CXX_MODULES BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}" FILES 
	"Source/Private/Surface.Impl.Windows.cppm"
	"Source/Private/Surface.Impl.Windows-MemoryManager.cppm"
	"Source/Private/Surface.Impl.Windows-MessageHandler.cppm"
	"Source/Private/Surface.Impl.Windows-RawInputDeviceContainer.cppm"
	"Source/Private/Surface.Impl.Windows-RawInputManager.cppm"
	"Source/Private/Surface.Impl.Windows-SurfaceService.cppm"
	"Source/Private/Surface.Impl.Windows-SurfaceServiceModule.cppm"
	"Source/Private/Surface.Impl.Windows-WindowClass.cppm"
)

message(VERBOSE "Configuring defines")
pony_validate_module_order(PONY_ENGINE_SURFACE_ORDER)
target_compile_definitions(PonyEngine.Surface.Impl PUBLIC
	PONY_ENGINE_SURFACE_ORDER=${PONY_ENGINE_SURFACE_ORDER}
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
