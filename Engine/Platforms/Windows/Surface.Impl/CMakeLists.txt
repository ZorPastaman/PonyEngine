message(STATUS "Configuring PonyEngine.Surface.Impl for Windows")

set(PONY_ENGINE_SURFACE_ORDER "p" CACHE STRING "PonyEngine.Surface.Impl module initialization order. Its first character must be in range [b-y].")

target_include_directories(PonyEngine.Surface.Impl PUBLIC
	"Include/Public"
)

target_sources(PonyEngine.Surface.Impl PUBLIC
	"Source/Launch.cpp"
)
target_sources(PonyEngine.Surface.Impl PRIVATE
	"Source/Launch.Impl.cpp"
)
target_sources(PonyEngine.Surface.Impl PRIVATE FILE_SET CXX_MODULES BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}" FILES 
	"Source/Main.cppm"
	"Source/Main-Cursor.cppm"
	"Source/Main-MessageHandler.cppm"
	"Source/Main-RawInputDeviceContainer.cppm"
	"Source/Main-RawInputManager.cppm"
	"Source/Main-SurfaceService.cppm"
	"Source/Main-SurfaceServiceModule.cppm"
	"Source/Main-WindowClass.cppm"
)

pony_validate_module_order(PONY_ENGINE_SURFACE_ORDER)
target_compile_definitions(PonyEngine.Surface.Impl PUBLIC
	PONY_ENGINE_SURFACE_ORDER=${PONY_ENGINE_SURFACE_ORDER}
)

if(NOT TARGET PonyEngine.Surface)
	message(FATAL_ERROR "PonyEngine.Surface wasn't configured")
endif()
target_link_libraries(PonyEngine.Surface.Impl PUBLIC
	PonyEngine.Application
)
target_link_libraries(PonyEngine.Surface.Impl PRIVATE
	PonyEngine.Core
	PonyEngine.Log
	PonyEngine.MessagePump
)
