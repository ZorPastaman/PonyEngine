message(STATUS "Configuring PonyEngine.Log.File.Impl feature module")

set(PONY_ENGINE_LOG_FILE_ORDER "p" CACHE STRING "PonyEngine.Log.File.Impl module initialization order. Its first character must be in range [b-y].")
set(PONY_ENGINE_LOG_FILE_PATH "Logs/Log.log" CACHE STRING "Log file path. It must be a relative path. The log file will be created in local data folder.")

add_library(PonyEngine.Log.File.Impl STATIC)

target_include_directories(PonyEngine.Log.File.Impl PUBLIC
	"Include/Public"
)

target_sources(PonyEngine.Log.File.Impl PUBLIC
	"Source/Launch.cpp"
)
target_sources(PonyEngine.Log.File.Impl PRIVATE
	"Source/Launch.Impl.cpp"
)
target_sources(PonyEngine.Log.File.Impl PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/File.cppm"
	"Source/File-FileLogger.cppm"
	"Source/File-FileLoggerModule.cppm"
)

pony_validate_module_order(PONY_ENGINE_LOG_FILE_ORDER)
pony_validate_path(PONY_ENGINE_LOG_FILE_PATH CAN_BE_RELATIVE)
target_compile_definitions(PonyEngine.Log.File.Impl PUBLIC
	PONY_ENGINE_LOG_FILE_ORDER=${PONY_ENGINE_LOG_FILE_ORDER}
)
target_compile_definitions(PonyEngine.Log.File.Impl PRIVATE
	PONY_ENGINE_LOG_FILE_PATH=${PONY_ENGINE_LOG_FILE_PATH}
)

set_target_properties(PonyEngine.Log.File.Impl PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.Log.File.Impl PUBLIC
	PonyEngine.Application
)
target_link_libraries(PonyEngine.Log.File.Impl PRIVATE
	PonyEngine.Core
	PonyEngine.Log
	PonyEngine.Log.Ext
)
