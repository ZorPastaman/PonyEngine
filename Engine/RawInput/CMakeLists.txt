message(STATUS "Configuring PonyEngine.RawInput")

message(VERBOSE "Configuring target")
add_library(PonyEngine.RawInput STATIC)

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.RawInput PUBLIC
	"Include/Public"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.RawInput PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Public/Main.cppm"
	"Source/Public/Main-Axis.cppm"
	"Source/Public/Main-AxisID.cppm"
	"Source/Public/Main-ConnectionEvent.cppm"
	"Source/Public/Main-DeviceHandle.cppm"
	"Source/Public/Main-DeviceType.cppm"
	"Source/Public/Main-DeviceTypeID.cppm"
	"Source/Public/Main-Gamepad.cppm"
	"Source/Public/Main-IDeviceObserver.cppm"
	"Source/Public/Main-InputEventType.cppm"
	"Source/Public/Main-IRawInputObserver.cppm"
	"Source/Public/Main-IRawInputService.cppm"
	"Source/Public/Main-IVibrating.cppm"
	"Source/Public/Main-Keyboard.cppm"
	"Source/Public/Main-Layout.cppm"
	"Source/Public/Main-Mouse.cppm"
	"Source/Public/Main-RawInputEvent.cppm"
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
