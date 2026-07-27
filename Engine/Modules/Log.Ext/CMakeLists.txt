message(STATUS "Configuring PonyEngine.Log.Ext")

if(NOT TARGET PonyEngine.Core)
	message(FATAL_ERROR "PonyEngine.Core wasn't configured")
endif()
if(NOT TARGET PonyEngine.Log)
	message(FATAL_ERROR "PonyEngine.Log wasn't configured")
endif()

message(VERBOSE "Configuring target")
add_library(PonyEngine.Log.Ext STATIC)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Log.Ext PUBLIC FILE_SET CXX_MODULES FILES 
	"Source/Main.cppm"
	"Source/Main-ILogger.cppm"
	"Source/Main-ILogHub.cppm"
	"Source/Main-LogEntry.cppm"
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Log.Ext PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Log.Ext PUBLIC
	PonyEngine.Core
	PonyEngine.Log
)
