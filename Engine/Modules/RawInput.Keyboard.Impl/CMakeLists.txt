message(STATUS "Configuring PonyEngine.RawInput.Keyboard.Impl feature module")

add_library(PonyEngine.RawInput.Keyboard.Impl STATIC)

target_sources(PonyEngine.RawInput.Keyboard.Impl PRIVATE FILE_SET CXX_MODULES FILES
	"Source/Keyboard.cppm"
	"Source/Keyboard-KeyboardController.cppm"
)

set_target_properties(PonyEngine.RawInput.Keyboard.Impl PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.RawInput.Keyboard.Impl PRIVATE
	PonyEngine.RawInput
	PonyEngine.RawInput.Ext
)
