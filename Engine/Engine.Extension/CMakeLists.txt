message(STATUS "Configuring PonyEngine.Engine.Extension")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Engine.Extension STATIC)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Engine.Extension PUBLIC FILE_SET CXX_MODULES FILES 
	"Source/Public/Engine.Extension/Engine.Extension.cppm"
	"Source/Public/Engine.Extension/Engine.Extension-IEngineContext.cppm"
	"Source/Public/Engine.Extension/Engine.Extension-ISystem.cppm"
	"Source/Public/Engine.Extension/Engine.Extension-ISystemFactory.cppm"
	"Source/Public/Engine.Extension/Engine.Extension-ISystemManager.cppm"
	"Source/Public/Engine.Extension/Engine.Extension-ITickableSystem.cppm"
	"Source/Public/Engine.Extension/Engine.Extension-SystemData.cppm"
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Engine.Extension PROPERTIES 
	CXX_STANDARD 23
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Engine.Extension PUBLIC
	PonyEngine.Core
)
