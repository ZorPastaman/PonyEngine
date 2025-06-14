message(STATUS "Configuring PonyEngine.Log.Ext")
add_library(PonyEngine.Log.Extension STATIC)

target_sources(PonyEngine.Log.Extension PUBLIC FILE_SET CXX_MODULES FILES 
	"Source/Public/Log.Extension/Log.Extension.cppm"
	"Source/Public/Log.Extension/Log.Extension-ISubLogger.cppm"
	"Source/Public/Log.Extension/Log.Extension-ISubLoggerFactory.cppm"
	"Source/Public/Log.Extension/Log.Extension-LogEntry.cppm"
)

message(STATUS "Configuring defines")
pony_set_log_mask(PonyEngine.Log.Extension TRUE)

message(STATUS "Setting build options")
pony_set_build_options(PonyEngine.Log.Extension TRUE)
set_target_properties(PonyEngine.Log.Extension PROPERTIES CXX_STANDARD 23)

message(STATUS "Configuring dependencies")
target_link_libraries(PonyEngine.Log.Extension PRIVATE
	PonyEngine.Core
)
