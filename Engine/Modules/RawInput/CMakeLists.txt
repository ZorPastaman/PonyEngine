message(STATUS "Configuring PonyEngine.RawInput feature module")

add_library(PonyEngine.RawInput STATIC)

target_include_directories(PonyEngine.RawInput PUBLIC
	"Include/Public"
)

target_sources(PonyEngine.RawInput PUBLIC FILE_SET CXX_MODULES FILES
	"Source/RawInput.cppm"
	"Source/RawInput-Axis.cppm"
	"Source/RawInput-ConnectionEvent.cppm"
	"Source/RawInput-DeviceHandle.cppm"
	"Source/RawInput-DeviceStyle.cppm"
	"Source/RawInput-DeviceType.cppm"
	"Source/RawInput-Gamepad.cppm"
	"Source/RawInput-InputEventType.cppm"
	"Source/RawInput-IRawInputObserver.cppm"
	"Source/RawInput-IRawInputService.cppm"
	"Source/RawInput-IVibrating.cppm"
	"Source/RawInput-Keyboard.cppm"
	"Source/RawInput-Layout.cppm"
	"Source/RawInput-Mouse.cppm"
	"Source/RawInput-RawInputEvent.cppm"
	"Source/RawInput-Style.cppm"
)

set_target_properties(PonyEngine.RawInput PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.RawInput PUBLIC
	PonyEngine.Core
)
