message(STATUS "Configuring PonyEngine.RawInput.Mouse.Impl for Windows")

message(VERBOSE "Configuring parameters")
set(PONY_ENGINE_RAW_INPUT_MOUSE_ORDER "p" CACHE STRING "PonyEngine.RawInput.Mouse.Impl module initialization order. Its first character must be in range [b-y].")

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.RawInput.Mouse.Impl PUBLIC
	"Include/Public"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.RawInput.Mouse.Impl PUBLIC
	"Source/Main.cpp"
)
target_sources(PonyEngine.RawInput.Mouse.Impl PRIVATE
	"Source/Main.Impl.cpp"
)
target_sources(PonyEngine.RawInput.Mouse.Impl PRIVATE FILE_SET CXX_MODULES BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}" FILES
	"Source/Private/Main.cppm"
	"Source/Private/Main-MouseProvider.cppm"
	"Source/Private/Main-MouseProviderModule.cppm"
)

message(VERBOSE "Configuring defines")
pony_validate_module_order(PONY_ENGINE_RAW_INPUT_MOUSE_ORDER)
target_compile_definitions(PonyEngine.RawInput.Mouse.Impl PUBLIC
	PONY_ENGINE_RAW_INPUT_MOUSE_ORDER=${PONY_ENGINE_RAW_INPUT_MOUSE_ORDER}
)

message(VERBOSE "Configuring dependencies")
if(NOT TARGET PonyEngine.Surface)
	message(FATAL_ERROR "PonyEngine.Surface wasn't configured")
endif()
target_link_libraries(PonyEngine.RawInput.Mouse.Impl PUBLIC
	PonyEngine.Application.Ext
)
target_link_libraries(PonyEngine.RawInput.Mouse.Impl PRIVATE
	PonyEngine.Log
	PonyEngine.Surface
)
