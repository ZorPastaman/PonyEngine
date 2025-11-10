message(STATUS "Configuring PonyEngine.Input.Ext")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Input.Ext STATIC)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Input.Ext PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Public/Input.Ext.cppm"
	"Source/Public/Input.Ext-DeviceData.cppm"
	"Source/Public/Input.Ext-IDevice.cppm"
	"Source/Public/Input.Ext-IInputContext.cppm" 
	"Source/Public/Input.Ext-IInputModuleContext.cppm"
	"Source/Public/Input.Ext-IInputProvider.cppm"
	"Source/Public/Input.Ext-InputProviderHandle.cppm"
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Input.Ext PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
if(NOT TARGET PonyEngine.Input)
	message(FATAL_ERROR "PonyEngine.Input wasn't configured")
endif()
target_link_libraries(PonyEngine.Input.Ext PRIVATE
	PonyEngine.Input
	PonyEngine.Core
	PonyEngine.Application.Ext
	PonyEngine.Log
)
