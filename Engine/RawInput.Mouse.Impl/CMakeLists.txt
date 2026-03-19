message(STATUS "Configuring PonyEngine.RawInput.Mouse.Impl")

message(VERBOSE "Configuring target")
add_library(PonyEngine.RawInput.Mouse.Impl STATIC)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.RawInput.Mouse.Impl PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Private/Main.cppm"
	"Source/Private/Main-MouseAxis.cppm"
	"Source/Private/Main-MouseAxisMap.cppm"
	"Source/Private/Main-MouseContainer.cppm"
	"Source/Private/Main-MouseEvent.cppm"
	"Source/Private/Main-MouseEventQueue.cppm"
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.RawInput.Mouse.Impl PROPERTIES 
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
target_link_libraries(PonyEngine.RawInput.Mouse.Impl PRIVATE
	PonyEngine.RawInput
	PonyEngine.RawInput.Ext
	PonyEngine.Core
)
