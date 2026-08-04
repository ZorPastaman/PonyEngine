message(STATUS "Configuring PonyEngine.RawInput.Keyboard.Impl for Windows")

if(NOT TARGET PonyEngine.Application)
	message(FATAL_ERROR "PonyEngine.Application wasn't configured")
endif()
if(NOT TARGET PonyEngine.Core)
	message(FATAL_ERROR "PonyEngine.Core wasn't configured")
endif()
if(NOT TARGET PonyEngine.Log)
	message(FATAL_ERROR "PonyEngine.Log wasn't configured")
endif()
if(NOT TARGET PonyEngine.WinAPIInput)
	message(FATAL_ERROR "PonyEngine.WinAPIInput wasn't configured")
endif()

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
	"Source/Main.cppm"
	"Source/Main-KeyboardAxisMap.cppm"
	"Source/Main-KeyboardProvider.cppm"
	"Source/Main-KeyboardProviderModule.cppm"
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
	PonyEngine.WinAPIInput
)
