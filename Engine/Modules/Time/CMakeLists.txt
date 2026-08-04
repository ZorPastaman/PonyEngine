message(STATUS "Configuring PonyEngine.Time")

if(NOT TARGET PonyEngine.Core)
	message(FATAL_ERROR "PonyEngine.Core wasn't configured")
endif()

add_library(PonyEngine.Time STATIC)

target_sources(PonyEngine.Time PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Main.cppm"
	"Source/Main-ITimeService.cppm"
)

set_target_properties(PonyEngine.Time PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.Time PUBLIC
	PonyEngine.Core
)
