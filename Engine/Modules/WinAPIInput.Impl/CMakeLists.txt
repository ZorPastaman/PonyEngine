message(STATUS "Configuring PonyEngine.WinAPIInput.Impl")

if(NOT TARGET PonyEngine.WinAPIInput)
	message(FATAL_ERROR "PonyEngine.WinAPIInput wasn't configured")
endif()

message(VERBOSE "Configuring target")
add_library(PonyEngine.WinAPIInput.Impl STATIC)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.WinAPIInput.Impl PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.WinAPIInput.Impl PRIVATE
	PonyEngine.WinAPIInput
)
