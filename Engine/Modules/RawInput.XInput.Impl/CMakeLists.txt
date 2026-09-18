message(STATUS "Configuring PonyEngine.RawInput.XInput.Impl feature module")

set(PONY_ENGINE_RAW_INPUT_XINPUT_ORDER "p" CACHE STRING "PonyEngine.RawInput.XInput.Impl module initialization order. Its first character must be in range [b-y].")

add_library(PonyEngine.RawInput.XInput.Impl STATIC)

target_include_directories(PonyEngine.RawInput.XInput.Impl PUBLIC
	"Include/Public"
)

target_sources(PonyEngine.RawInput.XInput.Impl PUBLIC
	"Source/Launch.cpp"
)
target_sources(PonyEngine.RawInput.XInput.Impl PRIVATE
	"Source/Launch.Impl.cpp"
)
target_sources(PonyEngine.RawInput.XInput.Impl PRIVATE FILE_SET CXX_MODULES BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}" FILES
	"Source/XInput.cppm"
	"Source/XInput-GamepadAxisMap.cppm"
	"Source/XInput-GamepadController.cppm"
	"Source/XInput-XInputProvider.cppm"
	"Source/XInput-XInputProviderModule.cppm"
)

pony_validate_module_order(PONY_ENGINE_RAW_INPUT_XINPUT_ORDER)
target_compile_definitions(PonyEngine.RawInput.XInput.Impl PUBLIC
	PONY_ENGINE_RAW_INPUT_XINPUT_ORDER=${PONY_ENGINE_RAW_INPUT_XINPUT_ORDER}
)

set_target_properties(PonyEngine.RawInput.XInput.Impl PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.RawInput.XInput.Impl PUBLIC
	PonyEngine.Application
)
target_link_libraries(PonyEngine.RawInput.XInput.Impl PRIVATE
	PonyEngine.Core
	PonyEngine.Log
	PonyEngine.RawInput
	PonyEngine.RawInput.Ext
	Xinput.lib
)
