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

set(PONY_ENGINE_JOB_ORDER "p" CACHE STRING "PonyEngine.Job.Impl module initialization order. Its first character must be in range [b-y].")
set(PONY_ENGINE_JOB_RESERVED_THREAD_COUNT "3" CACHE STRING "PonyEngine.Job.Impl service reserved thread count. Those are threads reserved for other purposes.")
set(PONY_ENGINE_JOB_MIN_THREAD_COUNT "2" CACHE STRING "PonyEngine.Job.Impl service minimal thread count.")
set(PONY_ENGINE_JOB_POOL_SIZE "64" CACHE STRING "PonyEngine.Job.Impl pool size of jobs per thread.")
set(PONY_ENGINE_JOB_THREAD_ROLE "Worker" CACHE STRING "PonyEngine.Job.Impl worker thread role.")

add_library(PonyEngine.Job.Impl STATIC)

target_include_directories(PonyEngine.Job.Impl PUBLIC
	"Include/Public"
)

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
	"Source/Main-JobQueue.cppm"
	"Source/Main-JobService.cppm"
	"Source/Main-JobServiceModule.cppm"
	"Source/Main-Worker.cppm"
)

pony_validate_module_order(PONY_ENGINE_JOB_ORDER)
target_compile_definitions(PonyEngine.Job.Impl PUBLIC
	PONY_ENGINE_JOB_ORDER=${PONY_ENGINE_JOB_ORDER}
)
target_compile_definitions(PonyEngine.Job.Impl PRIVATE
	PONY_ENGINE_JOB_RESERVED_THREAD_COUNT=${PONY_ENGINE_JOB_RESERVED_THREAD_COUNT}
	PONY_ENGINE_JOB_MIN_THREAD_COUNT=${PONY_ENGINE_JOB_MIN_THREAD_COUNT}
	PONY_ENGINE_JOB_POOL_SIZE=${PONY_ENGINE_JOB_POOL_SIZE}
	PONY_ENGINE_JOB_THREAD_ROLE=${PONY_ENGINE_JOB_THREAD_ROLE}
)

set_target_properties(PonyEngine.Job.Impl PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.Job.Impl PUBLIC
	PonyEngine.Application
)
target_link_libraries(PonyEngine.Job.Impl PRIVATE
	PonyEngine.Job
	PonyEngine.Core
	PonyEngine.Log
)
