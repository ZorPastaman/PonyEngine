message(STATUS "Configuring PonyEngine.Engine.Ext")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Engine.Ext STATIC)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Engine.Ext PUBLIC FILE_SET CXX_MODULES FILES 
	"Source/Public/Engine.Ext/Engine.Ext.cppm"
	"Source/Public/Engine.Ext/Engine.Ext-IEngineContext.cppm"
	"Source/Public/Engine.Ext/Engine.Ext-ISystem.cppm"
	"Source/Public/Engine.Ext/Engine.Ext-ISystemFactory.cppm"
	"Source/Public/Engine.Ext/Engine.Ext-ISystemManager.cppm"
	"Source/Public/Engine.Ext/Engine.Ext-ITickableSystem.cppm"
	"Source/Public/Engine.Ext/Engine.Ext-SystemData.cppm"
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Engine.Ext PROPERTIES 
	CXX_STANDARD 23
	OUTPUT_NAME "PonyEngine.Engine.Extension"
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Engine.Ext PRIVATE
	PonyEngine.Core
)
