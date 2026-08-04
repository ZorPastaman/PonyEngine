message(STATUS "Configuring PonyEngine.Job")

if(NOT TARGET PonyEngine.Core)
	message(FATAL_ERROR "PonyEngine.Core wasn't configured")
endif()

add_library(PonyEngine.Job STATIC)

target_sources(PonyEngine.Job PUBLIC FILE_SET CXX_MODULES FILES 
	"Source/Main.cppm"
	"Source/Main-IJobService.cppm"
	"Source/Main-ITask.cppm"
	"Source/Main-JobHandle.cppm"
)

set_target_properties(PonyEngine.Job PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.Job PUBLIC
	PonyEngine.Core
)
