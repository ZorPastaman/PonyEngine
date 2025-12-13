message(STATUS "Configuring PonyEngine.RawInput.Keyboard.Impl")

message(VERBOSE "Configuring parameters")
set(PONY_ENGINE_RAW_INPUT_KEYBOARD_ORDER "p" CACHE STRING "PonyEngine.RawInput.Keyboard.Impl module initialization order. Its first character must be in range [b-y].")

message(VERBOSE "Configuring target")
add_library(PonyEngine.RawInput.Keyboard.Impl STATIC)

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.RawInput.Keyboard.Impl PUBLIC
	"Include/Public/Common"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.RawInput.Keyboard.Impl PUBLIC
	"Source/Main.cpp"
)
target_sources(PonyEngine.RawInput.Keyboard.Impl PRIVATE
	"Source/Main.Impl.cpp"
)
target_sources(PonyEngine.RawInput.Keyboard.Impl PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Private/RawInput.Keyboard.Impl.cppm"
	"Source/Private/RawInput.Keyboard.Impl-Keyboard.cppm"
	"Source/Private/RawInput.Keyboard.Impl-KeyboardContainer.cppm"
	"Source/Private/RawInput.Keyboard.Impl-KeyboardEvent.cppm"
	"Source/Private/RawInput.Keyboard.Impl-KeyboardEventQueue.cppm"
)

if(PONY_WINDOWS)
	message(VERBOSE "Configuring sources for Windows")
	target_sources(PonyEngine.RawInput.Keyboard.Impl PRIVATE FILE_SET CXX_MODULES FILES
		"Source/Private/RawInput.Keyboard.Impl-Windows.KeyboardAxisMap.cppm"
		"Source/Private/RawInput.Keyboard.Impl-Windows.KeyboardProvider.cppm"
		"Source/Private/RawInput.Keyboard.Impl-Windows.KeyboardProviderModule.cppm"
	)
endif()

message(VERBOSE "Configuring defines")
pony_validate_module_order(PONY_ENGINE_RAW_INPUT_KEYBOARD_ORDER)
target_compile_definitions(PonyEngine.RawInput.Keyboard.Impl PUBLIC
	PONY_ENGINE_RAW_INPUT_KEYBOARD_ORDER=${PONY_ENGINE_RAW_INPUT_KEYBOARD_ORDER}
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.RawInput.Keyboard.Impl PROPERTIES 
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
target_link_libraries(PonyEngine.RawInput.Keyboard.Impl PUBLIC
	PonyEngine.Application.Ext
)
target_link_libraries(PonyEngine.RawInput.Keyboard.Impl PRIVATE
	PonyEngine.RawInput
	PonyEngine.RawInput.Ext
	PonyEngine.Core
	PonyEngine.Log
	PonyEngine.Surface
)
