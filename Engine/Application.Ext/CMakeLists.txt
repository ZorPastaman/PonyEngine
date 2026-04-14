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
	"Source/Main.cppm"
	"Source/Main-FlowState.cppm"
	"Source/Main-IApplicationContext.cppm"
	"Source/Main-ILoggerContext.cppm"
	"Source/Main-ILoggerModuleContext.cppm"
	"Source/Main-IModule.cppm"
	"Source/Main-IModuleContext.cppm"
	"Source/Main-IService.cppm"
	"Source/Main-IServiceInterfaceAdder.cppm"
	"Source/Main-IServiceModuleContext.cppm"
	"Source/Main-ITickableService.cppm"
	"Source/Main-ITickableServiceAdder.cppm"
	"Source/Main-LoggerHandle.cppm"
	"Source/Main-ModuleDataHandle.cppm"
	"Source/Main-ServiceHandle.cppm"
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
