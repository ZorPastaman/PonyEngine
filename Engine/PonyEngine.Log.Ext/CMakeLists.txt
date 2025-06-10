message(STATUS "Configuring PonyEngine.Log.Ext")
add_library(PonyEngine.Log.Ext STATIC)

target_sources(PonyEngine.Log.Ext PUBLIC FILE_SET CXX_MODULES FILES 
	"Source/Public/Log.Ext/Log.Ext.cppm"
	"Source/Public/Log.Ext/Log.Ext-ISubLogger.cppm"
	"Source/Public/Log.Ext/Log.Ext-ISubLoggerFactory.cppm"
	"Source/Public/Log.Ext/Log.Ext-LogEntry.cppm"
)

message(STATUS "Configuring defines")
pony_set_log_mask(PonyEngine.Log.Ext TRUE)

message(STATUS "Setting build options")
pony_set_build_options(PonyEngine.Log.Ext TRUE)
set_target_properties(PonyEngine.Log.Ext PROPERTIES CXX_STANDARD 23)

message(STATUS "Configuring dependencies")
target_link_libraries(PonyEngine.Log.Ext PRIVATE
	PonyEngine.Core
)
