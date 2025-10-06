message(STATUS "Configuring PonyEngine.Log.Main")

message(VERBOSE "Validating settings")
if(NOT TARGET PonyEngine.Log.Extension)
	message(FATAL_ERROR "PonyEngine.Log.Extension wasn't configured")
endif()

if(NOT PONY_ENGINE_LOG_MAIN_ORDER)
	message(FATAL_ERROR "PONY_ENGINE_LOG_MAIN is set but PONY_ENGINE_LOG_MAIN_ORDER isn't")
endif()
string(SUBSTRING "${PONY_ENGINE_LOG_MAIN_ORDER}" 0 1 ORDER_FIRST_CHAR)
if(NOT ORDER_FIRST_CHAR MATCHES "^[b-y]$")
	message(FATAL_ERROR "PONY_ENGINE_LOG_MAIN_ORDER is incorrect. Its first letter must be inside b-y range")
endif()

message(VERBOSE "Configuring target")
add_library(PonyEngine.Log.Main STATIC)

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.Log.Main PUBLIC
	"Include/Public/Common"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Log.Main PUBLIC
	"Source/Main.cpp"
)
target_sources(PonyEngine.Log.Main PRIVATE
	"Source/Main.Impl.cpp"
)
target_sources(PonyEngine.Log.Main PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Private/Log.Main/Log.Main.cppm"
	"Source/Private/Log.Main/Log.Main-Logger.cppm"
	"Source/Private/Log.Main/Log.Main-LoggerModule.cppm"
)

message(VERBOSE "Configuring defines")
target_compile_definitions(PonyEngine.Log.Main PUBLIC PONY_ENGINE_LOG_MAIN_ORDER=${PONY_ENGINE_LOG_MAIN_ORDER})

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Log.Main PROPERTIES 
	CXX_STANDARD 23
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Log.Main PUBLIC
	PonyEngine.Core
	PonyEngine.Log.Extension
)
