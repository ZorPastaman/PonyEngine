message(STATUS "Configuring PonyEngine.Log.Console.Impl feature module")

set(PONY_ENGINE_LOG_CONSOLE_ORDER "p" CACHE STRING "PonyEngine.Log.Console.Impl module initialization order. Its first character must be in range [b-y].")

add_library(PonyEngine.Log.Console.Impl STATIC)

target_include_directories(PonyEngine.Log.Console.Impl PUBLIC
	"Include/Public"
)

target_sources(PonyEngine.Log.Console.Impl PUBLIC
	"Source/Launch.cpp"
)
target_sources(PonyEngine.Log.Console.Impl PRIVATE
	"Source/Launch.Impl.cpp"
)
target_sources(PonyEngine.Log.Console.Impl PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Console.cppm"
	"Source/Console-ConsoleLogger.cppm"
	"Source/Console-ConsoleLoggerModule.cppm"
)

pony_validate_module_order(PONY_ENGINE_LOG_CONSOLE_ORDER)
target_compile_definitions(PonyEngine.Log.Console.Impl PUBLIC 
	PONY_ENGINE_LOG_CONSOLE_ORDER=${PONY_ENGINE_LOG_CONSOLE_ORDER}
)

set_target_properties(PonyEngine.Log.Console.Impl PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.Log.Console.Impl PUBLIC
	PonyEngine.Application
)
target_link_libraries(PonyEngine.Log.Console.Impl PRIVATE
	PonyEngine.Core
	PonyEngine.Log
	PonyEngine.Log.Ext
)
