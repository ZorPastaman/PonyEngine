message(STATUS "Configuring PonyEngine.RawInput.XInput.Impl")

message(VERBOSE "Configuring target")
add_library(PonyEngine.RawInput.XInput.Impl STATIC)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.RawInput.XInput.Impl PROPERTIES 
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
target_link_libraries(PonyEngine.RawInput.XInput.Impl PRIVATE
	PonyEngine.RawInput
	PonyEngine.RawInput.Ext
)
