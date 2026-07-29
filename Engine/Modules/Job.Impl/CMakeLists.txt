message(STATUS "Configuring PonyEngine.Job.Impl")

if(NOT TARGET PonyEngine.Application)
	message(FATAL_ERROR "PonyEngine.Application wasn't configured")
endif()
if(NOT TARGET PonyEngine.Core)
	message(FATAL_ERROR "PonyEngine.Core wasn't configured")
endif()
if(NOT TARGET PonyEngine.Job)
	message(FATAL_ERROR "PonyEngine.Job wasn't configured")
endif()
if(NOT TARGET PonyEngine.Log)
	message(FATAL_ERROR "PonyEngine.Log wasn't configured")
endif()

message(VERBOSE "Configuring parameters")
set(PONY_ENGINE_JOB_ORDER "p" CACHE STRING "PonyEngine.Job.Impl module initialization order. Its first character must be in range [b-y].")
set(PONY_ENGINE_JOB_RESERVED_THREAD_COUNT "3" CACHE STRING "PonyEngine.Job.Impl service reserved thread count. Those are threads reserved for other purposes.")
set(PONY_ENGINE_JOB_MIN_THREAD_COUNT "2" CACHE STRING "PonyEngine.Job.Impl service minimal thread count.")
set(PONY_ENGINE_JOB_POOL_SIZE "64" CACHE STRING "PonyEngine.Job.Impl pool size of jobs per thread.")

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
	"Source/Main-JobID.cppm"
	"Source/Main-JobPool.cppm"
	"Source/Main-JobService.cppm"
	"Source/Main-JobServiceModule.cppm"
	"Source/Main-Worker.cppm"
)

message(VERBOSE "Configuring defines")
pony_validate_module_order(PONY_ENGINE_JOB_ORDER)
target_compile_definitions(PonyEngine.Job.Impl PUBLIC
	PONY_ENGINE_JOB_ORDER=${PONY_ENGINE_JOB_ORDER}
)
target_compile_definitions(PonyEngine.Job.Impl PRIVATE
	PONY_ENGINE_JOB_RESERVED_THREAD_COUNT=${PONY_ENGINE_JOB_RESERVED_THREAD_COUNT}
	PONY_ENGINE_JOB_MIN_THREAD_COUNT=${PONY_ENGINE_JOB_MIN_THREAD_COUNT}
	PONY_ENGINE_JOB_POOL_SIZE=${PONY_ENGINE_JOB_POOL_SIZE}
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Job.Impl PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Job.Impl PUBLIC
	PonyEngine.Application
)
target_link_libraries(PonyEngine.Job.Impl PRIVATE
	PonyEngine.Job
	PonyEngine.Core
	PonyEngine.Log
)
