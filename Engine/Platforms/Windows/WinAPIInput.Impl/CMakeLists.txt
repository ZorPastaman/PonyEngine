message(STATUS "Configuring PonyEngine.WinAPIInput.Impl for Windows")

if(NOT TARGET PonyEngine.Application)
	message(FATAL_ERROR "PonyEngine.Application wasn't configured")
endif()
if(NOT TARGET PonyEngine.Core)
	message(FATAL_ERROR "PonyEngine.Core wasn't configured")
endif()
if(NOT TARGET PonyEngine.Log)
	message(FATAL_ERROR "PonyEngine.Log wasn't configured")
endif()

set(PONY_ENGINE_WINAPI_INPUT_ORDER "p" CACHE STRING "PonyEngine.WinAPIInput.Impl module initialization order. Its first character must be in range [b-y].")

target_include_directories(PonyEngine.WinAPIInput.Impl PUBLIC
	"Include/Public"
)

target_sources(PonyEngine.WinAPIInput.Impl PUBLIC
	"Source/Launch.cpp"
)
target_sources(PonyEngine.WinAPIInput.Impl PRIVATE
	"Source/Launch.Impl.cpp"
)
target_sources(PonyEngine.WinAPIInput.Impl PUBLIC FILE_SET CXX_MODULES BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}" FILES
	"Source/Main.cppm"
	"Source/Main-InputDispatcher.cppm"
	"Source/Main-InputDispatcherModule.cppm"
)

pony_validate_module_order(PONY_ENGINE_WINAPI_INPUT_ORDER)
target_compile_definitions(PonyEngine.WinAPIInput.Impl PUBLIC
	PONY_ENGINE_WINAPI_INPUT_ORDER=${PONY_ENGINE_WINAPI_INPUT_ORDER}
)

target_link_libraries(PonyEngine.WinAPIInput.Impl PUBLIC
	PonyEngine.Application
)
target_link_libraries(PonyEngine.WinAPIInput.Impl PRIVATE
	PonyEngine.Core
	PonyEngine.Log
)
