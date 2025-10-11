message(STATUS "Configuring PonyEngine.Application.Extension")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Application.Extension STATIC)

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.Application.Extension PUBLIC
	"Include/Public/Common"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Application.Extension PUBLIC FILE_SET CXX_MODULES FILES 
	"Source/Public/Application.Extension/Application.Extension.cppm"
	"Source/Public/Application.Extension/Application.Extension-FlowState.cppm"
	"Source/Public/Application.Extension/Application.Extension-IApplicationContext.cppm"
	"Source/Public/Application.Extension/Application.Extension-ILoggerContext.cppm"
	"Source/Public/Application.Extension/Application.Extension-ILoggerModuleContext.cppm"
	"Source/Public/Application.Extension/Application.Extension-IMessageObserver.cppm"
	"Source/Public/Application.Extension/Application.Extension-IModule.cppm"
	"Source/Public/Application.Extension/Application.Extension-IModuleContext.cppm"
	"Source/Public/Application.Extension/Application.Extension-IService.cppm"
	"Source/Public/Application.Extension/Application.Extension-IServiceModuleContext.cppm"
	"Source/Public/Application.Extension/Application.Extension-ITickableService.cppm"
	"Source/Public/Application.Extension/Application.Extension-LoggerHandle.cppm"
	"Source/Public/Application.Extension/Application.Extension-ModuleDataHandle.cppm"
	"Source/Public/Application.Extension/Application.Extension-ServiceData.cppm"
	"Source/Public/Application.Extension/Application.Extension-ServiceHandle.cppm"
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Application.Extension PROPERTIES 
	CXX_STANDARD 23
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Application.Extension PUBLIC
	PonyEngine.Core
	PonyEngine.Log
)
