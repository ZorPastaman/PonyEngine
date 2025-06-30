message(STATUS "Configuring PonyEngine.Log.Ext")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Log.Ext STATIC)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Log.Ext PUBLIC FILE_SET CXX_MODULES FILES 
	"Source/Public/Log.Ext/Log.Ext.cppm"
	"Source/Public/Log.Ext/Log.Ext-ILoggerContext.cppm"
	"Source/Public/Log.Ext/Log.Ext-ISubLogger.cppm"
	"Source/Public/Log.Ext/Log.Ext-ISubLoggerFactory.cppm"
	"Source/Public/Log.Ext/Log.Ext-LogEntry.cppm"
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Log.Ext PROPERTIES 
	CXX_STANDARD 23
	OUTPUT_NAME "PonyEngine.Log.Extension"
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Log.Ext PRIVATE
	PonyEngine.Core
)
