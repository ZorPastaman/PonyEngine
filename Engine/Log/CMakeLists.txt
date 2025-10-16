message(STATUS "Configuring PonyEngine.Log")

message(VERBOSE "Configuring environment")
include("CMake/Log.cmake")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Log STATIC)

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.Log PUBLIC
	"Include/Public/Common"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Log PUBLIC FILE_SET CXX_MODULES FILES 
	"Source/Public/Log/Log.cppm"
	"Source/Public/Log/Log-ILogger.cppm"
	"Source/Public/Log/Log-LogData.cppm"
	"Source/Public/Log/Log-LogFormat.cppm"
	"Source/Public/Log/Log-LogHelper.cppm"
	"Source/Public/Log/Log-LogType.cppm"
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Log PROPERTIES 
	CXX_STANDARD 23
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Log PRIVATE
	PonyEngine.Core
)
