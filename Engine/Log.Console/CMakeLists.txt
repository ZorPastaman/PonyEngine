message(STATUS "Configuring PonyEngine.Log.Console")

message(VERBOSE "Validating settings")
if(NOT PONY_ENGINE_LOG_CONSOLE_ORDER)
	message(FATAL_ERROR "PONY_ENGINE_LOG_CONSOLE is set but PONY_ENGINE_LOG_CONSOLE_ORDER isn't")
endif()
string(SUBSTRING "${PONY_ENGINE_LOG_CONSOLE_ORDER}" 0 1 ORDER_FIRST_CHAR)
if(NOT ORDER_FIRST_CHAR MATCHES "^[b-y]$")
	message(FATAL_ERROR "PONY_ENGINE_LOG_CONSOLE is incorrect. Its first letter must be inside b-y range")
endif()

if(NOT TARGET PonyEngine.Log.Extension)
	message(FATAL_ERROR "PonyEngine.Log.Extension wasn't configured")
endif()

message(VERBOSE "Configuring target")
add_library(PonyEngine.Log.Console STATIC)

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.Log.Console PUBLIC
	"Include/Public/Common"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Log.Console PUBLIC
	"Source/Main.cpp"
)
target_sources(PonyEngine.Log.Console PRIVATE
	"Source/Main.Impl.cpp"
)
target_sources(PonyEngine.Log.Console PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Private/Log.Console/Log.Console.cppm"
	"Source/Private/Log.Console/Log.Console-ConsoleSubLogger.cppm"
	"Source/Private/Log.Console/Log.Console-ConsoleSubLoggerFactory.cppm"
	"Source/Private/Log.Console/Log.Console-ConsoleSubLoggerModule.cppm"
)

message(VERBOSE "Configuring defines")
target_compile_definitions(PonyEngine.Log.Console PUBLIC PONY_ENGINE_LOG_CONSOLE_ORDER=${PONY_ENGINE_LOG_CONSOLE_ORDER})

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Log.Console PROPERTIES 
	CXX_STANDARD 23
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Log.Console PUBLIC
	PonyEngine.Core
	PonyEngine.Log.Extension
)
