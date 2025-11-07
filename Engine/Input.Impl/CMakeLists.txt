message(STATUS "Configuring PonyEngine.Input.Impl")

message(VERBOSE "Configuring parameters")
set(PONY_ENGINE_INPUT_ORDER "p" CACHE STRING "PonyEngine.Input.Impl module initialization order. Its first character must be in range [b-y].")
set(PONY_ENGINE_INPUT_TICK_ORDER "0" CACHE STRING "PonyEngine.Input.Impl service tick order. It must be an int32 number.")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Input.Impl STATIC)

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.Input.Impl PUBLIC
	"Include/Public/Common"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Input.Impl PUBLIC
	"Source/Main.cpp"
)
target_sources(PonyEngine.Input.Impl PRIVATE
	"Source/Main.Impl.cpp"
)
target_sources(PonyEngine.Input.Impl PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Private/Input.Impl.cppm"
	"Source/Private/Input.Impl-InputService.cppm"
	"Source/Private/Input.Impl-InputServiceModule.cppm"
)

message(VERBOSE "Configuring defines")
pony_validate_module_order(PONY_ENGINE_INPUT_ORDER)
pony_validate_tick_order(PONY_ENGINE_INPUT_TICK_ORDER)
target_compile_definitions(PonyEngine.Input.Impl PUBLIC
	PONY_ENGINE_INPUT_ORDER=${PONY_ENGINE_INPUT_ORDER}
	PONY_ENGINE_INPUT_TICK_ORDER=${PONY_ENGINE_INPUT_TICK_ORDER}
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Input.Impl PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Input.Impl PUBLIC
	PonyEngine.Core
	PonyEngine.Application.Ext
)
if(NOT TARGET PonyEngine.Input)
	message(FATAL_ERROR "PonyEngine.Input wasn't configured")
endif()
if(NOT TARGET PonyEngine.Input.Ext)
	message(FATAL_ERROR "PonyEngine.Input.Ext wasn't configured")
endif()
target_link_libraries(PonyEngine.Input.Impl PRIVATE
	PonyEngine.Input
	PonyEngine.Input.Ext
	PonyEngine.Log
)
