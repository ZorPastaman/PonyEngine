message(STATUS "Configuring PonyEngine.Application.Ext")

message(VERBOSE "Configuring environment")
include("CMake/Module.cmake")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Application.Ext STATIC)

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.Application.Ext PUBLIC
	"Include/Public"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Application.Ext PUBLIC FILE_SET CXX_MODULES FILES 
	"Source/Public/Main.cppm"
	"Source/Public/Main-FlowState.cppm"
	"Source/Public/Main-IApplicationContext.cppm"
	"Source/Public/Main-ILoggerContext.cppm"
	"Source/Public/Main-ILoggerModuleContext.cppm"
	"Source/Public/Main-IModule.cppm"
	"Source/Public/Main-IModuleContext.cppm"
	"Source/Public/Main-IService.cppm"
	"Source/Public/Main-IServiceInterfaceAdder.cppm"
	"Source/Public/Main-IServiceModuleContext.cppm"
	"Source/Public/Main-ITickableService.cppm"
	"Source/Public/Main-ITickableServiceAdder.cppm"
	"Source/Public/Main-LoggerHandle.cppm"
	"Source/Public/Main-ModuleDataHandle.cppm"
	"Source/Public/Main-ServiceHandle.cppm"
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Application.Ext PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Application.Ext PUBLIC
	PonyEngine.Core
	PonyEngine.Log
)
