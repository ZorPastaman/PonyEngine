message(STATUS "Configuring PonyEngine.Time")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Time STATIC)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Time PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Public/Time.cppm"
	"Source/Public/Time-ITimeService.cppm"
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Time PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Time PRIVATE
	PonyEngine.Core
)
