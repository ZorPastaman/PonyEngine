message(STATUS "Configuring PonyEngine.Time")

if(NOT TARGET PonyEngine.Core)
	message(FATAL_ERROR "PonyEngine.Core wasn't configured")
endif()

message(VERBOSE "Configuring target")
add_library(PonyEngine.Time STATIC)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Time PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Main.cppm"
	"Source/Main-ITimeService.cppm"
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Time PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Time PUBLIC
	PonyEngine.Core
)
