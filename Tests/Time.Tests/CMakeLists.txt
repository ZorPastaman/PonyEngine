message(STATUS "Configuring PonyEngine.Time.Tests")
add_executable(PonyEngine.Time.Tests)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Time.Tests PRIVATE
	"Time/Utility.cpp"
)

message(VERBOSE "Configuring defines")
pony_set_log_defines(PonyEngine.Time.Tests ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL})
target_compile_definitions(PonyEngine.Time.Tests PRIVATE 
	$<$<BOOL:${PONY_ENGINE_TESTING_BENCHMARK}>:PONY_ENGINE_TESTING_BENCHMARK>
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Time.Tests PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Setting build options")
pony_set_build_options(PonyEngine.Time.Tests ${PONY_ENGINE_OPTIMIZATION})

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Time.Tests PRIVATE 
	Catch2::Catch2WithMain
	PonyEngine.Time
	PonyEngine.Core
)

message(VERBOSE "Discovering tests")
catch_discover_tests(PonyEngine.Time.Tests)
