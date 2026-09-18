message(STATUS "Configuring PonyEngine.Job feature module")

add_library(PonyEngine.Job STATIC)

target_sources(PonyEngine.Job PUBLIC FILE_SET CXX_MODULES FILES 
	"Source/Job.cppm"
	"Source/Job-IJobService.cppm"
	"Source/Job-JobHandle.cppm"
)

set_target_properties(PonyEngine.Job PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.Job PUBLIC
	PonyEngine.Core
)
