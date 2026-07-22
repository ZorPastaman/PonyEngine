message(STATUS "Configuring PonyEngine.Log.PlatformConsole.Impl")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Log.PlatformConsole.Impl STATIC)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Log.PlatformConsole.Impl PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)
