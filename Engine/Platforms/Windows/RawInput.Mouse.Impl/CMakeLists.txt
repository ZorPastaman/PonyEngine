message(STATUS "Configuring PonyEngine.RawInput.Mouse.Impl for Windows")

if(NOT TARGET PonyEngine.Application)
	message(FATAL_ERROR "PonyEngine.Application wasn't configured")
endif()
if(NOT TARGET PonyEngine.Log)
	message(FATAL_ERROR "PonyEngine.Log wasn't configured")
endif()
if(NOT TARGET PonyEngine.WinAPIInput)
	message(FATAL_ERROR "PonyEngine.WinAPIInput wasn't configured")
endif()

set(PONY_ENGINE_RAW_INPUT_MOUSE_ORDER "p" CACHE STRING "PonyEngine.RawInput.Mouse.Impl module initialization order. Its first character must be in range [b-y].")

target_include_directories(PonyEngine.RawInput.Mouse.Impl PUBLIC
	"Include/Public"
)

target_sources(PonyEngine.RawInput.Mouse.Impl PUBLIC
	"Source/Launch.cpp"
)
target_sources(PonyEngine.RawInput.Mouse.Impl PRIVATE
	"Source/Launch.Impl.cpp"
)
target_sources(PonyEngine.RawInput.Mouse.Impl PRIVATE FILE_SET CXX_MODULES BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}" FILES
	"Source/Main.cppm"
	"Source/Main-MouseProvider.cppm"
	"Source/Main-MouseProviderModule.cppm"
)

pony_validate_module_order(PONY_ENGINE_RAW_INPUT_MOUSE_ORDER)
target_compile_definitions(PonyEngine.RawInput.Mouse.Impl PUBLIC
	PONY_ENGINE_RAW_INPUT_MOUSE_ORDER=${PONY_ENGINE_RAW_INPUT_MOUSE_ORDER}
)

target_link_libraries(PonyEngine.RawInput.Mouse.Impl PUBLIC
	PonyEngine.Application
)
target_link_libraries(PonyEngine.RawInput.Mouse.Impl PRIVATE
	PonyEngine.Log
	PonyEngine.WinAPIInput
)
