message(STATUS "Configuring PonyEngine.Log.File")

message(VERBOSE "Validating settings")
if(NOT PONY_ENGINE_LOG_FILE_ORDER)
	message(FATAL_ERROR "PONY_ENGINE_LOG_FILE is set but PONY_ENGINE_LOG_FILE_ORDER isn't")
endif()
string(SUBSTRING "${PONY_ENGINE_LOG_FILE_ORDER}" 0 1 ORDER_FIRST_CHAR)
if(NOT ORDER_FIRST_CHAR MATCHES "^[b-y]$")
	message(FATAL_ERROR "PONY_ENGINE_LOG_FILE_ORDER is incorrect. Its first letter must be inside b-y range")
endif()

if(NOT PONY_ENGINE_LOG_FILE_PATH)
	message(FATAL_ERROR "PONY_ENGINE_LOG_FILE is set but PONY_ENGINE_LOG_FILE_PATH isn't")
endif()
if(IS_ABSOLUTE PONY_ENGINE_LOG_FILE_PATH)
	message(FATAL_ERROR "PONY_ENGINE_LOG_FILE_PATH isn't relative")
endif()
if(NOT PONY_ENGINE_LOG_FILE_PATH MATCHES "^[A-Za-z0-9._/-]+$")
	message(FATAL_ERROR "PONY_ENGINE_LOG_FILE_PATH contains invalid symbols")
endif()
foreach(path_component IN LISTS PONY_ENGINE_LOG_FILE_PATH)
	string(TOLOWER "${path_component}" path_component_lower)
	if("${path_component_lower}" MATCHES "^(con|prn|aux|nul|com[1-9]|lpt[1-9])(\\..*)?$")
		message(FATAL_ERROR "PONY_ENGINE_LOG_FILE_PATH contains invalid component names")
	endif()
endforeach()

if(NOT TARGET PonyEngine.Log.Extension)
	message(FATAL_ERROR "PonyEngine.Log.Extension wasn't configured")
endif()

message(VERBOSE "Configuring target")
add_library(PonyEngine.Log.File STATIC)

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.Log.File PUBLIC
	"Include/Public/Common"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Log.File PUBLIC
	"Source/Main.cpp"
)
target_sources(PonyEngine.Log.File PRIVATE
	"Source/Main.Impl.cpp"
)
target_sources(PonyEngine.Log.File PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Private/Log.File/Log.File.cppm"
	"Source/Private/Log.File/Log.File-FileSubLogger.cppm"
	"Source/Private/Log.File/Log.File-FileSubLoggerFactory.cppm"
	"Source/Private/Log.File/Log.File-FileSubLoggerModule.cppm"
)

message(VERBOSE "Configuring defines")
target_compile_definitions(PonyEngine.Log.File PUBLIC
	PONY_ENGINE_LOG_FILE_ORDER=${PONY_ENGINE_LOG_FILE_ORDER} PONY_ENGINE_LOG_FILE_PATH=${PONY_ENGINE_LOG_FILE_PATH}
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Log.File PROPERTIES 
	CXX_STANDARD 23
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Log.File PUBLIC
	PonyEngine.Core
	PonyEngine.Log.Extension
	PonyEngine.Path
)
