message(STATUS "Configuring PonyEngine.RawInput")

message(VERBOSE "Configuring target")
add_library(PonyEngine.RawInput STATIC)

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.RawInput PUBLIC
	"Include/Public/Common"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.RawInput PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Public/RawInput.cppm"
	"Source/Public/RawInput-Axis.cppm"
	"Source/Public/RawInput-AxisId.cppm"
	"Source/Public/RawInput-ConnectionEvent.cppm"
	"Source/Public/RawInput-DeviceHandle.cppm"
	"Source/Public/RawInput-DeviceType.cppm"
	"Source/Public/RawInput-DeviceTypeId.cppm"
	"Source/Public/RawInput-Gamepad.cppm"
	"Source/Public/RawInput-IDeviceObserver.cppm"
	"Source/Public/RawInput-InputEventType.cppm"
	"Source/Public/RawInput-IRawInputObserver.cppm"
	"Source/Public/RawInput-IRawInputService.cppm"
	"Source/Public/RawInput-IVibrating.cppm"
	"Source/Public/RawInput-Keyboard.cppm"
	"Source/Public/RawInput-Layout.cppm"
	"Source/Public/RawInput-Mouse.cppm"
	"Source/Public/RawInput-RawInputEvent.cppm"
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.RawInput PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.RawInput PUBLIC
	PonyEngine.Core
)
