message(STATUS "Configuring PonyEngine.RawInput.Ext")

if(NOT TARGET PonyEngine.Core)
	message(FATAL_ERROR "PonyEngine.Core wasn't configured")
endif()
if(NOT TARGET PonyEngine.RawInput)
	message(FATAL_ERROR "PonyEngine.RawInput wasn't configured")
endif()

message(VERBOSE "Configuring target")
add_library(PonyEngine.RawInput.Ext STATIC)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.RawInput.Ext PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Main.cppm"
	"Source/Main-DeviceParams.cppm"
	"Source/Main-FeatureEntry.cppm"
	"Source/Main-IDeviceController.cppm"
	"Source/Main-IDeviceHub.cppm"
	"Source/Main-IInputRegistry.cppm"
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.RawInput.Ext PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.RawInput.Ext PUBLIC
	PonyEngine.Core
	PonyEngine.RawInput
)
