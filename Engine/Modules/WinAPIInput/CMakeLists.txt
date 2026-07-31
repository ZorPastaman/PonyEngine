message(STATUS "Configuring PonyEngine.WinAPIInput")

message(VERBOSE "Configuring target")
add_library(PonyEngine.WinAPIInput STATIC)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.WinAPIInput PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)
