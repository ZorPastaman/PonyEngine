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
	"Source/Public/Log.cppm"
	"Source/Public/Log-ILogger.cppm"
	"Source/Public/Log-LogData.cppm"
	"Source/Public/Log-LogFormat.cppm"
	"Source/Public/Log-LogHelper.cppm"
	"Source/Public/Log-LogType.cppm"
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Log PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Log PRIVATE
	PonyEngine.Core
)
