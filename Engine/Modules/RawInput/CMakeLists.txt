message(STATUS "Configuring PonyEngine.RawInput")

if(NOT TARGET PonyEngine.Core)
	message(FATAL_ERROR "PonyEngine.Core wasn't configured")
endif()

add_library(PonyEngine.RawInput STATIC)

target_include_directories(PonyEngine.RawInput PUBLIC
	"Include/Public"
)

target_sources(PonyEngine.RawInput PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Main.cppm"
	"Source/Main-Axis.cppm"
	"Source/Main-ConnectionEvent.cppm"
	"Source/Main-DeviceHandle.cppm"
	"Source/Main-DeviceStyle.cppm"
	"Source/Main-DeviceType.cppm"
	"Source/Main-Gamepad.cppm"
	"Source/Main-InputEventType.cppm"
	"Source/Main-IRawInputObserver.cppm"
	"Source/Main-IRawInputService.cppm"
	"Source/Main-IVibrating.cppm"
	"Source/Main-Keyboard.cppm"
	"Source/Main-Layout.cppm"
	"Source/Main-Mouse.cppm"
	"Source/Main-RawInputEvent.cppm"
	"Source/Main-Style.cppm"
)

set_target_properties(PonyEngine.RawInput PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.RawInput PUBLIC
	PonyEngine.Core
)
