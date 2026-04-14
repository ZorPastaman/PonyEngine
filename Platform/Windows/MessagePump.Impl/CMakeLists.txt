message(STATUS "Configuring PonyEngine.MessagePump for Windows")

message(VERBOSE "Configuring parameters")
set(PONY_ENGINE_MESSAGE_PUMP_ORDER "p" CACHE STRING "PonyEngine.MessagePump.Impl module initialization order. Its first character must be in range [b-y].")
set(PONY_ENGINE_MESSAGE_PUMP_TICK_ORDER "0" CACHE STRING "PonyEngine.MessagePump.Impl service tick order. It must be an int32 number.")

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.MessagePump.Impl PUBLIC
	"Include/Public"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.MessagePump.Impl PUBLIC
	"Source/Launch.cpp"
)
target_sources(PonyEngine.MessagePump.Impl PRIVATE
	"Source/Launch.Impl.cpp"
)
target_sources(PonyEngine.MessagePump.Impl PUBLIC FILE_SET CXX_MODULES BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}" FILES
	"Source/Main.cppm"
	"Source/Main-MessagePumpService.cppm"
	"Source/Main-MessagePumpServiceModule.cppm"
)

message(VERBOSE "Configuring defines")
pony_validate_module_order(PONY_ENGINE_MESSAGE_PUMP_ORDER)
pony_validate_tick_order(PONY_ENGINE_MESSAGE_PUMP_TICK_ORDER)
target_compile_definitions(PonyEngine.MessagePump.Impl PUBLIC
	PONY_ENGINE_MESSAGE_PUMP_ORDER=${PONY_ENGINE_MESSAGE_PUMP_ORDER}
	PONY_ENGINE_MESSAGE_PUMP_TICK_ORDER=${PONY_ENGINE_MESSAGE_PUMP_TICK_ORDER}
)

message(VERBOSE "Configuring dependencies")
if(NOT TARGET PonyEngine.MessagePump)
	message(FATAL_ERROR "PonyEngine.MessagePump wasn't configured")
endif()
target_link_libraries(PonyEngine.MessagePump.Impl PUBLIC
	PonyEngine.Application.Ext
)
target_link_libraries(PonyEngine.MessagePump.Impl PRIVATE
	PonyEngine.Core
	PonyEngine.Log
)
