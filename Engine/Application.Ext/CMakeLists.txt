message(STATUS "Configuring PonyEngine.Application.Ext")

message(VERBOSE "Configuring environment")
include("CMake/Module.cmake")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Application.Ext STATIC)

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.Application.Ext PUBLIC
	"Include/Public/Common"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Application.Ext PUBLIC FILE_SET CXX_MODULES FILES 
	"Source/Public/Application.Ext.cppm"
	"Source/Public/Application.Ext-FlowState.cppm"
	"Source/Public/Application.Ext-IApplicationContext.cppm"
	"Source/Public/Application.Ext-ILoggerContext.cppm"
	"Source/Public/Application.Ext-ILoggerModuleContext.cppm"
	"Source/Public/Application.Ext-IModule.cppm"
	"Source/Public/Application.Ext-IModuleContext.cppm"
	"Source/Public/Application.Ext-IService.cppm"
	"Source/Public/Application.Ext-IServiceModuleContext.cppm"
	"Source/Public/Application.Ext-ITickableService.cppm"
	"Source/Public/Application.Ext-LoggerHandle.cppm"
	"Source/Public/Application.Ext-ModuleDataHandle.cppm"
	"Source/Public/Application.Ext-ServiceData.cppm"
	"Source/Public/Application.Ext-ServiceHandle.cppm"
)

if(PONY_WINDOWS)
	message(VERBOSE "Configuring sources for Windows")
	target_sources(PonyEngine.Application.Ext PUBLIC FILE_SET CXX_MODULES FILES
		"Source/Public/Application.Ext-Windows.IApplicationContext.cppm"
	)
endif()

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
