message(STATUS "Configuring PonyEngine.RawInput.Impl")

message(VERBOSE "Configuring parameters")
set(PONY_ENGINE_RAW_INPUT_ORDER "p" CACHE STRING "PonyEngine.RawInput.Impl module initialization order. Its first character must be in range [b-y].")
set(PONY_ENGINE_RAW_INPUT_TICK_ORDER "0" CACHE STRING "PonyEngine.RawInput.Impl service tick order. It must be an int32 number.")

message(VERBOSE "Configuring target")
add_library(PonyEngine.RawInput.Impl STATIC)

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.RawInput.Impl PUBLIC
	"Include/Public/Common"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.RawInput.Impl PUBLIC
	"Source/Main.cpp"
)
target_sources(PonyEngine.RawInput.Impl PRIVATE
	"Source/Main.Impl.cpp"
)
target_sources(PonyEngine.RawInput.Impl PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Private/RawInput.Impl.cppm"
	"Source/Private/RawInput.Impl-Device.cppm"
	"Source/Private/RawInput.Impl-InputDeviceContainer.cppm"
	"Source/Private/RawInput.Impl-InputProviderContainer.cppm"
	"Source/Private/RawInput.Impl-RawInputQueue.cppm"
	"Source/Private/RawInput.Impl-RawInputService.cppm"
	"Source/Private/RawInput.Impl-RawInputServiceModule.cppm"
)

message(VERBOSE "Configuring defines")
pony_validate_module_order(PONY_ENGINE_RAW_INPUT_ORDER)
pony_validate_tick_order(PONY_ENGINE_RAW_INPUT_TICK_ORDER)
target_compile_definitions(PonyEngine.RawInput.Impl PUBLIC
	PONY_ENGINE_RAW_INPUT_ORDER=${PONY_ENGINE_RAW_INPUT_ORDER}
	PONY_ENGINE_RAW_INPUT_TICK_ORDER=${PONY_ENGINE_RAW_INPUT_TICK_ORDER}
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.RawInput.Impl PROPERTIES 
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
target_link_libraries(PonyEngine.RawInput.Impl PUBLIC
	PonyEngine.Application.Ext
)
target_link_libraries(PonyEngine.RawInput.Impl PRIVATE
	PonyEngine.RawInput
	PonyEngine.RawInput.Ext
	PonyEngine.Core
	PonyEngine.Log
)
