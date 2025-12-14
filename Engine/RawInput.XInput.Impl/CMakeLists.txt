message(STATUS "Configuring PonyEngine.RawInput.XInput.Impl")

message(VERBOSE "Configuring parameters")
set(PONY_ENGINE_RAW_INPUT_XINPUT_ORDER "p" CACHE STRING "PonyEngine.RawInput.XInput.Impl module initialization order. Its first character must be in range [b-y].")

message(VERBOSE "Configuring target")
add_library(PonyEngine.RawInput.XInput.Impl STATIC)

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.RawInput.XInput.Impl PUBLIC
	"Include/Public/Common"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.RawInput.XInput.Impl PUBLIC
	"Source/Main.cpp"
)
target_sources(PonyEngine.RawInput.XInput.Impl PRIVATE
	"Source/Main.Impl.cpp"
)
target_sources(PonyEngine.RawInput.XInput.Impl PRIVATE FILE_SET CXX_MODULES FILES
	"Source/Private/RawInput.XInput.Impl.cppm"
)

if(PONY_WINDOWS)
	message(VERBOSE "Configuring sources for Windows")
	target_sources(PonyEngine.RawInput.XInput.Impl PRIVATE FILE_SET CXX_MODULES FILES
		"Source/Private/RawInput.XInput.Impl-Windows.Gamepad.cppm"
		"Source/Private/RawInput.XInput.Impl-Windows.GamepadVibrator.cppm"
	)
endif()

message(VERBOSE "Configuring defines")
pony_validate_module_order(PONY_ENGINE_RAW_INPUT_XINPUT_ORDER)
target_compile_definitions(PonyEngine.RawInput.XInput.Impl PUBLIC
	PONY_ENGINE_RAW_INPUT_XINPUT_ORDER=${PONY_ENGINE_RAW_INPUT_XINPUT_ORDER}
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.RawInput.XInput.Impl PROPERTIES 
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
target_link_libraries(PonyEngine.RawInput.XInput.Impl PUBLIC
	PonyEngine.Application.Ext
)
target_link_libraries(PonyEngine.RawInput.XInput.Impl PRIVATE
	PonyEngine.RawInput
	PonyEngine.RawInput.Ext
	PonyEngine.Core
	PonyEngine.Log
	PonyEngine.Surface
)
if(PONY_WINDOWS)
	target_link_libraries(PonyEngine.RawInput.XInput.Impl PRIVATE
		Xinput.lib
	)
endif()
