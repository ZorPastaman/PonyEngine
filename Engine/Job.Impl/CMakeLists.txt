message(STATUS "Configuring PonyEngine.Job.Impl")

message(VERBOSE "Configuring parameters")
set(PONY_ENGINE_JOB_ORDER "p" CACHE STRING "PonyEngine.Job.Impl module initialization order. Its first character must be in range [b-y].")
set(PONY_ENGINE_JOB_RESERVED_THREAD_COUNT "3" CACHE STRING "PonyEngine.Job.Impl service reserved thread count. Those are threads reserved for other purposes.")
set(PONY_ENGINE_JOB_MIN_THREAD_COUNT "2" CACHE STRING "PonyEngine.Job.Impl service minimal thread count.")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Job.Impl STATIC)

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.Job.Impl PUBLIC
	"Include/Public"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Job.Impl PUBLIC
	"Source/Launch.cpp"
)
target_sources(PonyEngine.Job.Impl PRIVATE
	"Source/Launch.Impl.cpp"
)
target_sources(PonyEngine.Job.Impl PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Main.cppm"
	"Source/Main-Job.cppm"
	"Source/Main-JobService.cppm"
	"Source/Main-JobServiceModule.cppm"
	"Source/Main-Worker.cppm"
)

message(VERBOSE "Configuring defines")
pony_validate_module_order(PONY_ENGINE_JOB_ORDER)
target_compile_definitions(PonyEngine.Job.Impl PUBLIC
	PONY_ENGINE_JOB_ORDER=${PONY_ENGINE_JOB_ORDER}
	PONY_ENGINE_JOB_RESERVED_THREAD_COUNT=${PONY_ENGINE_JOB_RESERVED_THREAD_COUNT}
	PONY_ENGINE_JOB_MIN_THREAD_COUNT=${PONY_ENGINE_JOB_MIN_THREAD_COUNT}
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Job.Impl PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
if(NOT TARGET PonyEngine.Job)
	message(FATAL_ERROR "PonyEngine.Job wasn't configured")
endif()
target_link_libraries(PonyEngine.Job.Impl PUBLIC
	PonyEngine.Application.Ext
)
target_link_libraries(PonyEngine.Job.Impl PRIVATE
	PonyEngine.Job
	PonyEngine.Core
	PonyEngine.Log
)
