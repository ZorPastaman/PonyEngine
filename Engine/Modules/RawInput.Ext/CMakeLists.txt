message(STATUS "Configuring PonyEngine.RawInput.Ext feature module")

add_library(PonyEngine.RawInput.Ext STATIC)

target_sources(PonyEngine.RawInput.Ext PUBLIC FILE_SET CXX_MODULES FILES
	"Source/RawInput.cppm"
	"Source/RawInput-DeviceParams.cppm"
	"Source/RawInput-FeatureEntry.cppm"
	"Source/RawInput-IDeviceController.cppm"
	"Source/RawInput-IDeviceHub.cppm"
	"Source/RawInput-IInputRegistry.cppm"
)

set_target_properties(PonyEngine.RawInput.Ext PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.RawInput.Ext PUBLIC
	PonyEngine.Core
	PonyEngine.RawInput
)
