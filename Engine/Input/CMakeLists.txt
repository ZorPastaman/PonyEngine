message(STATUS "Configuring PonyEngine.Input")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Input STATIC)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Input PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Public/Input.cppm"
	"Source/Public/Input-ActionBindingHandle.cppm"
	"Source/Public/Input-ActionId.cppm"
	"Source/Public/Input-Axis.cppm"
	"Source/Public/Input-AxisBinding.cppm"
	"Source/Public/Input-BiasModifier.cppm"
	"Source/Public/Input-ClampModifier.cppm"
	"Source/Public/Input-DeadZoneModifier.cppm"
	"Source/Public/Input-DeviceHandle.cppm"
	"Source/Public/Input-GamepadLayout.cppm"
	"Source/Public/Input-IDeviceObserver.cppm"
	"Source/Public/Input-IInputObserver.cppm"
	"Source/Public/Input-IInputService.cppm"
	"Source/Public/Input-IModifier.cppm"
	"Source/Public/Input-InputEvent.cppm"
	"Source/Public/Input-InputEventType.cppm"
	"Source/Public/Input-IRawInputObserver.cppm"
	"Source/Public/Input-IVibrating.cppm"
	"Source/Public/Input-KeyboardLayout.cppm"
	"Source/Public/Input-MouseLayout.cppm"
	"Source/Public/Input-RawInputEvent.cppm"
	"Source/Public/Input-ScaleModifier.cppm"
	"Source/Public/Input-VibrationState.cppm"
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Input PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Input PRIVATE
	PonyEngine.Core
)
