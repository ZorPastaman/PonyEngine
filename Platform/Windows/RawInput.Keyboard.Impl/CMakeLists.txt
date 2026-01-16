message(STATUS "Configuring PonyEngine.RawInput.Keyboard.Impl for Windows")

message(VERBOSE "Configuring parameters")
set(PONY_ENGINE_RAW_INPUT_KEYBOARD_ORDER "p" CACHE STRING "PonyEngine.RawInput.Keyboard.Impl module initialization order. Its first character must be in range [b-y].")

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.RawInput.Keyboard.Impl PUBLIC
	"Include/Public"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.RawInput.Keyboard.Impl PUBLIC
	"Source/Main.cpp"
)
target_sources(PonyEngine.RawInput.Keyboard.Impl PRIVATE
	"Source/Main.Impl.cpp"
)
target_sources(PonyEngine.RawInput.Keyboard.Impl PRIVATE FILE_SET CXX_MODULES BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}" FILES
	"Source/Private/Main.cppm"
	"Source/Private/Main-KeyboardAxisMap.cppm"
	"Source/Private/Main-KeyboardProvider.cppm"
	"Source/Private/Main-KeyboardProviderModule.cppm"
)

message(VERBOSE "Configuring defines")
pony_validate_module_order(PONY_ENGINE_RAW_INPUT_KEYBOARD_ORDER)
target_compile_definitions(PonyEngine.RawInput.Keyboard.Impl PUBLIC
	PONY_ENGINE_RAW_INPUT_KEYBOARD_ORDER=${PONY_ENGINE_RAW_INPUT_KEYBOARD_ORDER}
)

message(VERBOSE "Configuring dependencies")
if(NOT TARGET PonyEngine.Surface)
	message(FATAL_ERROR "PonyEngine.Surface wasn't configured")
endif()
target_link_libraries(PonyEngine.RawInput.Keyboard.Impl PUBLIC
	PonyEngine.Application.Ext
)
target_link_libraries(PonyEngine.RawInput.Keyboard.Impl PRIVATE
	PonyEngine.Log
	PonyEngine.Surface
)
