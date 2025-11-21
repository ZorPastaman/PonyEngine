message(STATUS "Configuring PonyEngine.Log.Impl")

message(VERBOSE "Configuring parameters")
set(PONY_ENGINE_LOG_ORDER "p" CACHE STRING "PonyEngine.Log.Impl module initialization order. Its first character must be in range [b-y].")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Log.Impl STATIC)

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.Log.Impl PUBLIC
	"Include/Public/Common"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Log.Impl PUBLIC
	"Source/Main.cpp"
)
target_sources(PonyEngine.Log.Impl PRIVATE
	"Source/Main.Impl.cpp"
)
target_sources(PonyEngine.Log.Impl PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Private/Log.Impl.cppm"
	"Source/Private/Log.Impl-LogFiller.cppm"
	"Source/Private/Log.Impl-Logger.cppm"
	"Source/Private/Log.Impl-LoggerModule.cppm"
	"Source/Private/Log.Impl-LogTypeSymbol.cppm"
	"Source/Private/Log.Impl-SubLoggerContainer.cppm"
)

message(VERBOSE "Configuring defines")
pony_validate_module_order(PONY_ENGINE_LOG_ORDER)
target_compile_definitions(PonyEngine.Log.Impl PUBLIC 
	PONY_ENGINE_LOG_ORDER=${PONY_ENGINE_LOG_ORDER}
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Log.Impl PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Log.Impl PUBLIC
	PonyEngine.Core
	PonyEngine.Application.Ext
)
if(NOT TARGET PonyEngine.Log.Ext)
	message(FATAL_ERROR "PonyEngine.Log.Ext wasn't configured")
endif()
target_link_libraries(PonyEngine.Log.Impl PUBLIC
	PonyEngine.Log
	PonyEngine.Log.Ext
)
