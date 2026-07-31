message(STATUS "Configuring PonyEngine.RawInput.Keyboard.Impl")

if(NOT TARGET PonyEngine.RawInput)
	message(FATAL_ERROR "PonyEngine.RawInput wasn't configured")
endif()
if(NOT TARGET PonyEngine.RawInput.Ext)
	message(FATAL_ERROR "PonyEngine.RawInput wasn't configured")
endif()

message(VERBOSE "Configuring target")
add_library(PonyEngine.RawInput.Keyboard.Impl STATIC)

target_sources(PonyEngine.RawInput.Keyboard.Impl PRIVATE FILE_SET CXX_MODULES FILES
	"Source/Main.cppm"
	"Source/Main-KeyboardController.cppm"
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.RawInput.Keyboard.Impl PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.RawInput.Keyboard.Impl PRIVATE
	PonyEngine.RawInput
	PonyEngine.RawInput.Ext
)
