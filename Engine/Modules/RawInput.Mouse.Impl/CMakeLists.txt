message(STATUS "Configuring PonyEngine.RawInput.Mouse.Impl")

if(NOT TARGET PonyEngine.Core)
	message(FATAL_ERROR "PonyEngine.Core wasn't configured")
endif()
if(NOT TARGET PonyEngine.RawInput)
	message(FATAL_ERROR "PonyEngine.RawInput wasn't configured")
endif()
if(NOT TARGET PonyEngine.RawInput.Ext)
	message(FATAL_ERROR "PonyEngine.RawInput.Ext wasn't configured")
endif()

message(VERBOSE "Configuring target")
add_library(PonyEngine.RawInput.Mouse.Impl STATIC)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.RawInput.Mouse.Impl PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Main.cppm"
	"Source/Main-MouseAxis.cppm"
	"Source/Main-MouseAxisMap.cppm"
	"Source/Main-MouseController.cppm"
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.RawInput.Mouse.Impl PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.RawInput.Mouse.Impl PRIVATE
	PonyEngine.Core
	PonyEngine.RawInput
	PonyEngine.RawInput.Ext
)
