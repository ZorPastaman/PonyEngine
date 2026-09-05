message(STATUS "Configuring PonyEngine.RawInput.Keyboard.Impl.WinAPI modification module")

set(PONY_ENGINE_RAW_INPUT_KEYBOARD_ORDER "p" CACHE STRING "PonyEngine.RawInput.Keyboard.Impl module initialization order. Its first character must be in range [b-y].")

target_include_directories(PonyEngine.RawInput.Keyboard.Impl PUBLIC
	"Include/Public"
)

target_sources(PonyEngine.RawInput.Keyboard.Impl PUBLIC
	"Source/Launch.cpp"
)
target_sources(PonyEngine.RawInput.Keyboard.Impl PRIVATE
	"Source/Launch.Impl.cpp"
)
target_sources(PonyEngine.RawInput.Keyboard.Impl PRIVATE FILE_SET CXX_MODULES BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}" FILES
	"Source/Keyboard.cppm"
	"Source/Keyboard-KeyboardAxisMap.cppm"
	"Source/Keyboard-KeyboardProvider.cppm"
	"Source/Keyboard-KeyboardProviderModule.cppm"
)

pony_validate_module_order(PONY_ENGINE_RAW_INPUT_KEYBOARD_ORDER)
target_compile_definitions(PonyEngine.RawInput.Keyboard.Impl PUBLIC
	PONY_ENGINE_RAW_INPUT_KEYBOARD_ORDER=${PONY_ENGINE_RAW_INPUT_KEYBOARD_ORDER}
)

target_link_libraries(PonyEngine.RawInput.Keyboard.Impl PUBLIC
	PonyEngine.Application
)
target_link_libraries(PonyEngine.RawInput.Keyboard.Impl PRIVATE
	PonyEngine.Core
	PonyEngine.Log
	PonyEngine.WinInput
)
