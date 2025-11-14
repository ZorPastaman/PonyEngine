message(STATUS "Configuring PonyEngine.Input.Keyboard.Impl")

message(VERBOSE "Configuring parameters")
set(PONY_ENGINE_INPUT_KEYBOARD_ORDER "p" CACHE STRING "PonyEngine.Input.Keyboard.Impl module initialization order. Its first character must be in range [b-y].")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Input.Keyboard.Impl STATIC)

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.Input.Keyboard.Impl PUBLIC
	"Include/Public/Common"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Input.Keyboard.Impl PUBLIC
	"Source/Main.cpp"
)
target_sources(PonyEngine.Input.Keyboard.Impl PRIVATE
	"Source/Main.Impl.cpp"
)
target_sources(PonyEngine.Input.Keyboard.Impl PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Private/Input.Keyboard.Impl.cppm"
	"Source/Private/Input.Keyboard.Impl-Keyboard.cppm"
	"Source/Private/Input.Keyboard.Impl-KeyboardContainer.cppm"
)

if(PONY_WINDOWS)
	message(VERBOSE "Configuring sources for Windows")
	target_sources(PonyEngine.Input.Keyboard.Impl PRIVATE FILE_SET CXX_MODULES FILES 
		"Source/Private/Input.Keyboard.Impl-Windows.KeyboardLayoutMap.cppm"
		"Source/Private/Input.Keyboard.Impl-Windows.KeyboardProvider.cppm"
		"Source/Private/Input.Keyboard.Impl-Windows.KeyboardProviderModule.cppm"
	)
endif()

message(VERBOSE "Configuring defines")
pony_validate_module_order(PONY_ENGINE_INPUT_KEYBOARD_ORDER)
target_compile_definitions(PonyEngine.Input.Keyboard.Impl PUBLIC
	PONY_ENGINE_INPUT_KEYBOARD_ORDER=${PONY_ENGINE_INPUT_KEYBOARD_ORDER}
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Input.Keyboard.Impl PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Input.Keyboard.Impl PUBLIC
	PonyEngine.Core
	PonyEngine.Application.Ext
)
if(NOT TARGET PonyEngine.Input)
	message(FATAL_ERROR "PonyEngine.Input wasn't configured")
endif()
if(NOT TARGET PonyEngine.Input.Ext)
	message(FATAL_ERROR "PonyEngine.Input.Ext wasn't configured")
endif()
target_link_libraries(PonyEngine.Input.Keyboard.Impl PRIVATE
	PonyEngine.Input
	PonyEngine.Input.Ext
	PonyEngine.Log
)
if(PONY_WINDOWS)
	if(NOT TARGET PonyEngine.Surface)
		message(FATAL_ERROR "PonyEngine.Surface wasn't configured")
	endif()
	target_link_libraries(PonyEngine.Input.Keyboard.Impl PRIVATE
		PonyEngine.Surface
	)
endif()
