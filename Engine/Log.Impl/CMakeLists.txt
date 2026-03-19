message(STATUS "Configuring PonyEngine.Log.Impl")

message(VERBOSE "Configuring parameters")
set(PONY_ENGINE_LOG_ORDER "p" CACHE STRING "PonyEngine.Log.Impl module initialization order. Its first character must be in range [b-y].")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Log.Impl STATIC)

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.Log.Impl PUBLIC
	"Include/Public"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Log.Impl PUBLIC
	"Source/Main.cpp"
)
target_sources(PonyEngine.Log.Impl PRIVATE
	"Source/Main.Impl.cpp"
)
target_sources(PonyEngine.Log.Impl PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Private/Main.cppm"
	"Source/Private/Main-LogFiller.cppm"
	"Source/Private/Main-Logger.cppm"
	"Source/Private/Main-LoggerModule.cppm"
	"Source/Private/Main-LogTypeSymbol.cppm"
	"Source/Private/Main-SubLoggerContainer.cppm"
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
if(NOT TARGET PonyEngine.Log.Ext)
	message(FATAL_ERROR "PonyEngine.Log.Ext wasn't configured")
endif()
target_link_libraries(PonyEngine.Log.Impl PUBLIC
	PonyEngine.Application.Ext
)
target_link_libraries(PonyEngine.Log.Impl PRIVATE
	PonyEngine.Log
	PonyEngine.Log.Ext
	PonyEngine.Core
)
