message(STATUS "Configuring PonyEngine.Log.PConsole.Impl for Windows")

if(NOT TARGET PonyEngine.Application)
	message(FATAL_ERROR "PonyEngine.Application wasn't configured")
endif()
if(NOT TARGET PonyEngine.Core)
	message(FATAL_ERROR "PonyEngine.Core wasn't configured")
endif()
if(NOT TARGET PonyEngine.Log)
	message(FATAL_ERROR "PonyEngine.Log wasn't configured")
endif()
if(NOT TARGET PonyEngine.Log.Ext)
	message(FATAL_ERROR "PonyEngine.Log.Ext wasn't configured")
endif()

message(VERBOSE "Configuring parameters")
set(PONY_ENGINE_LOG_PCONSOLE_ORDER "p" CACHE STRING "PonyEngine.Log.PConsole.Impl module initialization order. Its first character must be in range [b-y].")

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.Log.PConsole.Impl PUBLIC
	"Include/Public"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Log.PConsole.Impl PUBLIC
	"Source/Launch.cpp"
)
target_sources(PonyEngine.Log.PConsole.Impl PRIVATE
	"Source/Launch.Impl.cpp"
)
target_sources(PonyEngine.Log.PConsole.Impl PRIVATE FILE_SET CXX_MODULES BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}" FILES
	"Source/Main.cppm"
	"Source/Main-PlatformConsoleLogger.cppm"
	"Source/Main-PlatformConsoleLoggerModule.cppm"
)

message(VERBOSE "Configuring defines")
pony_validate_module_order(PONY_ENGINE_LOG_PCONSOLE_ORDER)
target_compile_definitions(PonyEngine.Log.PConsole.Impl PUBLIC 
	PONY_ENGINE_LOG_PCONSOLE_ORDER=${PONY_ENGINE_LOG_PCONSOLE_ORDER}
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Log.PConsole.Impl PUBLIC
	PonyEngine.Application
)
target_link_libraries(PonyEngine.Log.PConsole.Impl PRIVATE
	PonyEngine.Core
	PonyEngine.Log
	PonyEngine.Log.Ext
)
