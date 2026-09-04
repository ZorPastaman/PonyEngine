message(STATUS "Configuring PonyEngine.Log.Ext feature module")

add_library(PonyEngine.Log.Ext STATIC)

target_sources(PonyEngine.Log.Ext PUBLIC FILE_SET CXX_MODULES FILES 
	"Source/Log.cppm"
	"Source/Log-ILogger.cppm"
	"Source/Log-ILogHub.cppm"
	"Source/Log-LogEntry.cppm"
)

set_target_properties(PonyEngine.Log.Ext PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.Log.Ext PUBLIC
	PonyEngine.Core
	PonyEngine.Log
)
