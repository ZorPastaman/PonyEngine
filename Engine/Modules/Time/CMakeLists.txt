message(STATUS "Configuring PonyEngine.Time feature module")

add_library(PonyEngine.Time STATIC)

target_sources(PonyEngine.Time PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Time.cppm"
	"Source/Time-ITimeService.cppm"
)

set_target_properties(PonyEngine.Time PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.Time PUBLIC
	PonyEngine.Core
)
