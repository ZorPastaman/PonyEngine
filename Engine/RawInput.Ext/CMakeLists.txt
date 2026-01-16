message(STATUS "Configuring PonyEngine.RawInput.Ext")

message(VERBOSE "Configuring target")
add_library(PonyEngine.RawInput.Ext STATIC)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.RawInput.Ext PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Public/Main.cppm"
	"Source/Public/Main-FeatureEntry.cppm"
	"Source/Public/Main-IInputProvider.cppm"
	"Source/Public/Main-InputProviderHandle.cppm"
	"Source/Public/Main-IRawInputContext.cppm" 
	"Source/Public/Main-IRawInputModuleContext.cppm"
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.RawInput.Ext PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
if(NOT TARGET PonyEngine.RawInput)
	message(FATAL_ERROR "PonyEngine.RawInput wasn't configured")
endif()
target_link_libraries(PonyEngine.RawInput.Ext PUBLIC
	PonyEngine.RawInput
	PonyEngine.Core
	PonyEngine.Application.Ext
	PonyEngine.Log
)
