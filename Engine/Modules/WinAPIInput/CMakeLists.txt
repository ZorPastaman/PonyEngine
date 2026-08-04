message(STATUS "Configuring PonyEngine.WinAPIInput")

add_library(PonyEngine.WinAPIInput STATIC)

set_target_properties(PonyEngine.WinAPIInput PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)
