message(STATUS "Configuring PonyEngine.Log.WinDebug.Impl feature module")

set(PONY_ENGINE_LOG_WINDEBUG_ORDER "p" CACHE STRING "PonyEngine.Log.WinDebug.Impl module initialization order. Its first character must be in range [b-y].")

add_library(PonyEngine.Log.WinDebug.Impl STATIC)

target_include_directories(PonyEngine.Log.WinDebug.Impl PUBLIC
	"Include/Public"
)

target_sources(PonyEngine.Log.WinDebug.Impl PUBLIC
	"Source/Launch.cpp"
)
target_sources(PonyEngine.Log.WinDebug.Impl PRIVATE
	"Source/Launch.Impl.cpp"
)
target_sources(PonyEngine.Log.WinDebug.Impl PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/WinDebug.cppm"
	"Source/WinDebug-WinDebugLogger.cppm"
	"Source/WinDebug-WinDebugLoggerModule.cppm"
)

pony_validate_module_order(PONY_ENGINE_LOG_WINDEBUG_ORDER)
target_compile_definitions(PonyEngine.Log.WinDebug.Impl PUBLIC 
	PONY_ENGINE_LOG_WINDEBUG_ORDER=${PONY_ENGINE_LOG_WINDEBUG_ORDER}
)

set_target_properties(PonyEngine.Log.WinDebug.Impl PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.Log.WinDebug.Impl PUBLIC
	PonyEngine.Application
)
target_link_libraries(PonyEngine.Log.WinDebug.Impl PRIVATE
	PonyEngine.Core
	PonyEngine.Log
	PonyEngine.Log.Ext
)
