message(STATUS "Configuring PonyEngine.RawInput.Mouse.Impl")

message(VERBOSE "Configuring parameters")
set(PONY_ENGINE_RAW_INPUT_MOUSE_ORDER "p" CACHE STRING "PonyEngine.RawInput.Mouse.Impl module initialization order. Its first character must be in range [b-y].")

message(VERBOSE "Configuring target")
add_library(PonyEngine.RawInput.Mouse.Impl STATIC)

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.RawInput.Mouse.Impl PUBLIC
	"Include/Public/Common"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.RawInput.Mouse.Impl PUBLIC
	"Source/Main.cpp"
)
target_sources(PonyEngine.RawInput.Mouse.Impl PRIVATE
	"Source/Main.Impl.cpp"
)
target_sources(PonyEngine.RawInput.Mouse.Impl PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Private/RawInput.Mouse.Impl.cppm"
	"Source/Private/RawInput.Mouse.Impl-Mouse.cppm"
	"Source/Private/RawInput.Mouse.Impl-MouseAxis.cppm"
	"Source/Private/RawInput.Mouse.Impl-MouseAxisMap.cppm"
	"Source/Private/RawInput.Mouse.Impl-MouseContainer.cppm"
	"Source/Private/RawInput.Mouse.Impl-MouseEvent.cppm"
	"Source/Private/RawInput.Mouse.Impl-MouseEventQueue.cppm"
)

if(PONY_WINDOWS)
	message(VERBOSE "Configuring sources for Windows")
	target_sources(PonyEngine.RawInput.Mouse.Impl PRIVATE FILE_SET CXX_MODULES FILES
		"Source/Private/RawInput.Mouse.Impl-Windows.MouseProvider.cppm"
		"Source/Private/RawInput.Mouse.Impl-Windows.MouseProviderModule.cppm"
	)
endif()

message(VERBOSE "Configuring defines")
pony_validate_module_order(PONY_ENGINE_RAW_INPUT_MOUSE_ORDER)
target_compile_definitions(PonyEngine.RawInput.Mouse.Impl PUBLIC
	PONY_ENGINE_RAW_INPUT_MOUSE_ORDER=${PONY_ENGINE_RAW_INPUT_MOUSE_ORDER}
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.RawInput.Mouse.Impl PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
if(NOT TARGET PonyEngine.RawInput)
	message(FATAL_ERROR "PonyEngine.RawInput wasn't configured")
endif()
if(NOT TARGET PonyEngine.RawInput.Ext)
	message(FATAL_ERROR "PonyEngine.RawInput.Ext wasn't configured")
endif()
if(NOT TARGET PonyEngine.Surface)
	message(FATAL_ERROR "PonyEngine.Surface wasn't configured")
endif()
target_link_libraries(PonyEngine.RawInput.Mouse.Impl PUBLIC
	PonyEngine.Application.Ext
)
target_link_libraries(PonyEngine.RawInput.Mouse.Impl PRIVATE
	PonyEngine.RawInput
	PonyEngine.RawInput.Ext
	PonyEngine.Core
	PonyEngine.Log
	PonyEngine.Surface
)
