message(STATUS "Configuring PonyEngine.RawInput.Keyboard.Impl")

message(VERBOSE "Configuring target")
add_library(PonyEngine.RawInput.Keyboard.Impl STATIC)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.RawInput.Keyboard.Impl PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Private/RawInput.Keyboard.Impl.cppm"
	"Source/Private/RawInput.Keyboard.Impl-KeyboardContainer.cppm"
	"Source/Private/RawInput.Keyboard.Impl-KeyboardEvent.cppm"
	"Source/Private/RawInput.Keyboard.Impl-KeyboardEventQueue.cppm"
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.RawInput.Keyboard.Impl PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
if(NOT TARGET PonyEngine.RawInput)
	message(FATAL_ERROR "PonyEngine.RawInput wasn't configured")
endif()
if(NOT TARGET PonyEngine.RawInput.Ext)
	message(FATAL_ERROR "PonyEngine.RawInput.Ext wasn't configured")
endif()
target_link_libraries(PonyEngine.RawInput.Keyboard.Impl PRIVATE
	PonyEngine.RawInput
	PonyEngine.RawInput.Ext
	PonyEngine.Core
)
