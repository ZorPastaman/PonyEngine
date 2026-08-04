message(STATUS "Configuring PonyEngine.Log.PConsole.Impl")

add_library(PonyEngine.Log.PConsole.Impl STATIC)

set_target_properties(PonyEngine.Log.PConsole.Impl PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)
