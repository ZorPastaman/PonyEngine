message(STATUS "Configuring PonyEngine.Log.File")

message(VERBOSE "Validating settings")
pony_validate_module_order(PONY_ENGINE_LOG_FILE_ORDER)
pony_validate_path(PONY_ENGINE_LOG_FILE_PATH false true)

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
	"Source/Private/Log.File/Log.File-FileSubLoggerModule.cppm"
)

message(VERBOSE "Configuring defines")
target_compile_definitions(PonyEngine.Log.File PUBLIC
	PONY_ENGINE_LOG_FILE_ORDER=${PONY_ENGINE_LOG_FILE_ORDER}
)
target_compile_definitions(PonyEngine.Log.File PRIVATE
	PONY_ENGINE_LOG_FILE_PATH=${PONY_ENGINE_LOG_FILE_PATH}
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Log.File PROPERTIES 
	CXX_STANDARD 23
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Log.File PUBLIC
	PonyEngine.Core
	PonyEngine.Application.Extension
)
target_link_libraries(PonyEngine.Log.File PRIVATE
	PonyEngine.Log
	PonyEngine.Log.Extension
)
