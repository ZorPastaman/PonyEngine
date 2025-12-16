message(STATUS "Configuring PonyEngine.Log.Ext")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Log.Ext STATIC)

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.Log.Ext PUBLIC
	"Include/Public/Common"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Log.Ext PUBLIC FILE_SET CXX_MODULES FILES 
	"Source/Public/Log.Ext.cppm"
	"Source/Public/Log.Ext-ILoggerContext.cppm"
	"Source/Public/Log.Ext-ILoggerModuleContext.cppm"
	"Source/Public/Log.Ext-ISubLogger.cppm"
	"Source/Public/Log.Ext-LogEntry.cppm"
	"Source/Public/Log.Ext-LogHelper.cppm"
	"Source/Public/Log.Ext-SubLoggerHandle.cppm"
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Log.Ext PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Log.Ext PUBLIC
	PonyEngine.Log
	PonyEngine.Core
	PonyEngine.Application.Ext
)
