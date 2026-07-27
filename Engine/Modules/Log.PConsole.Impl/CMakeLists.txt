message(STATUS "Configuring PonyEngine.Log.PConsole.Impl")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Log.PConsole.Impl STATIC)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Log.PConsole.Impl PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)
