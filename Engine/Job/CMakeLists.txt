message(STATUS "Configuring PonyEngine.Job")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Job STATIC)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Job PUBLIC FILE_SET CXX_MODULES FILES 
	"Source/Main.cppm"
	"Source/Main-IJob.cppm"
	"Source/Main-IJobService.cppm"
	"Source/Main-ITask.cppm"
	"Source/Main-JobStatus.cppm"
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Job PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Job PUBLIC
	PonyEngine.Core
)
