message(STATUS "Configuring PonyEngine.Display.Impl feature module")

add_library(PonyEngine.Display.Impl STATIC)

target_sources(PonyEngine.Display.Impl PRIVATE FILE_SET CXX_MODULES FILES
	"Source/Display.cppm"
)

set_target_properties(PonyEngine.Display.Impl PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.Display.Impl PUBLIC
	PonyEngine.Core
	PonyEngine.Display
)
