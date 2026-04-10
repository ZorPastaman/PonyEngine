message(STATUS "Configuring PonyEngine.RawInput")

message(VERBOSE "Configuring target")
add_library(PonyEngine.RawInput STATIC)

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.RawInput PUBLIC
	"Include/Public"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.RawInput PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Main.cppm"
	"Source/Main-Axis.cppm"
	"Source/Main-AxisID.cppm"
	"Source/Main-ConnectionEvent.cppm"
	"Source/Main-DeviceHandle.cppm"
	"Source/Main-DeviceType.cppm"
	"Source/Main-DeviceTypeID.cppm"
	"Source/Main-Gamepad.cppm"
	"Source/Main-IDeviceObserver.cppm"
	"Source/Main-InputEventType.cppm"
	"Source/Main-IRawInputObserver.cppm"
	"Source/Main-IRawInputService.cppm"
	"Source/Main-IVibrating.cppm"
	"Source/Main-Keyboard.cppm"
	"Source/Main-Layout.cppm"
	"Source/Main-Mouse.cppm"
	"Source/Main-RawInputEvent.cppm"
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
