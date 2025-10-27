message(STATUS "Configuring PonyEngine.Log.File.Impl")

message(VERBOSE "Configuring parameters")
set(PONY_ENGINE_LOG_FILE_ORDER "p" CACHE STRING "PonyEngine.Log.File.Impl module initialization order. Its first character must be in range [b-y].")
set(PONY_ENGINE_LOG_FILE_PATH "Logs/Log.log" CACHE STRING "Log file path. It must be a relative path. The log file will be created in local data folder.")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Log.File.Impl STATIC)

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.Log.File.Impl PUBLIC
	"Include/Public/Common"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Log.File.Impl PUBLIC
	"Source/Main.cpp"
)
target_sources(PonyEngine.Log.File.Impl PRIVATE
	"Source/Main.Impl.cpp"
)
target_sources(PonyEngine.Log.File.Impl PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Private/Log.File.Impl.cppm"
	"Source/Private/Log.File.Impl-FileSubLogger.cppm"
	"Source/Private/Log.File.Impl-FileSubLoggerModule.cppm"
)

message(VERBOSE "Configuring defines")
pony_validate_module_order(PONY_ENGINE_LOG_FILE_ORDER)
pony_validate_path(PONY_ENGINE_LOG_FILE_PATH false true)
target_compile_definitions(PonyEngine.Log.File.Impl PUBLIC
	PONY_ENGINE_LOG_FILE_ORDER=${PONY_ENGINE_LOG_FILE_ORDER}
)
target_compile_definitions(PonyEngine.Log.File.Impl PRIVATE
	PONY_ENGINE_LOG_FILE_PATH=${PONY_ENGINE_LOG_FILE_PATH}
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Log.File.Impl PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Log.File.Impl PUBLIC
	PonyEngine.Core
	PonyEngine.Application.Ext
)
if(NOT TARGET PonyEngine.Log.Ext)
	message(FATAL_ERROR "PonyEngine.Log.Ext wasn't configured")
endif()
target_link_libraries(PonyEngine.Log.File.Impl PRIVATE
	PonyEngine.Log
	PonyEngine.Log.Ext
)
