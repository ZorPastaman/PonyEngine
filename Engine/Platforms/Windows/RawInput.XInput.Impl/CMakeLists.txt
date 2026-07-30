message(STATUS "Configuring PonyEngine.RawInput.XInput.Impl fow Windows")

if(NOT TARGET PonyEngine.Application)
	message(FATAL_ERROR "PonyEngine.Application wasn't configured")
endif()
if(NOT TARGET PonyEngine.Core)
	message(FATAL_ERROR "PonyEngine.Core wasn't configured")
endif()
if(NOT TARGET PonyEngine.Log)
	message(FATAL_ERROR "PonyEngine.Log wasn't configured")
endif()

message(VERBOSE "Configuring parameters")
set(PONY_ENGINE_RAW_INPUT_XINPUT_ORDER "p" CACHE STRING "PonyEngine.RawInput.XInput.Impl module initialization order. Its first character must be in range [b-y].")

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.RawInput.XInput.Impl PUBLIC
	"Include/Public"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.RawInput.XInput.Impl PUBLIC
	"Source/Launch.cpp"
)
target_sources(PonyEngine.RawInput.XInput.Impl PRIVATE
	"Source/Launch.Impl.cpp"
)
target_sources(PonyEngine.RawInput.XInput.Impl PRIVATE FILE_SET CXX_MODULES BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}" FILES
	"Source/Main.cppm"
	"Source/Main-GamepadAxisMap.cppm"
	"Source/Main-GamepadController.cppm"
	"Source/Main-XInputProvider.cppm"
	"Source/Main-XInputProviderModule.cppm"
)

message(VERBOSE "Configuring defines")
pony_validate_module_order(PONY_ENGINE_RAW_INPUT_XINPUT_ORDER)
target_compile_definitions(PonyEngine.RawInput.XInput.Impl PUBLIC
	PONY_ENGINE_RAW_INPUT_XINPUT_ORDER=${PONY_ENGINE_RAW_INPUT_XINPUT_ORDER}
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.RawInput.XInput.Impl PUBLIC
	PonyEngine.Application
)
target_link_libraries(PonyEngine.RawInput.XInput.Impl PRIVATE
	PonyEngine.Core
	PonyEngine.Log
)
target_link_libraries(PonyEngine.RawInput.XInput.Impl PRIVATE
	Xinput.lib
)
