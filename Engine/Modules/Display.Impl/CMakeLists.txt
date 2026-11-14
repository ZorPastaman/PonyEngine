message(STATUS "Configuring PonyEngine.Display.Impl feature module")

add_library(PonyEngine.Display.Impl STATIC)

set_target_properties(PonyEngine.Display.Impl PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.Display.Impl PUBLIC
	PonyEngine.Core
	PonyEngine.Display
)
