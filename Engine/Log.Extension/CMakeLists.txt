message(STATUS "Configuring PonyEngine.Log.Extension")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Log.Extension STATIC)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Log.Extension PUBLIC FILE_SET CXX_MODULES FILES 
	"Source/Public/Log.Extension/Log.Extension.cppm"
	"Source/Public/Log.Extension/Log.Extension-ILoggerContext.cppm"
	"Source/Public/Log.Extension/Log.Extension-ILoggerModuleContext.cppm"
	"Source/Public/Log.Extension/Log.Extension-ISubLogger.cppm"
	"Source/Public/Log.Extension/Log.Extension-LogEntry.cppm"
	"Source/Public/Log.Extension/Log.Extension-SubLoggerHandle.cppm"
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Log.Extension PROPERTIES 
	CXX_STANDARD 23
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Log.Extension PRIVATE
	PonyEngine.Log
	PonyEngine.Core
	PonyEngine.Application.Extension
)
