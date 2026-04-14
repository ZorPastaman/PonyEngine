message(STATUS "Configuring PonyEngine.Surface.Tests")
add_executable(PonyEngine.Surface.Tests)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Surface.Tests PRIVATE
	"Surface/Utility.cpp"
)

message(VERBOSE "Configuring defines")
pony_set_log_defines(PonyEngine.Surface.Tests ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL})
target_compile_definitions(PonyEngine.Surface.Tests PRIVATE 
	$<$<BOOL:${PONY_ENGINE_TESTING_BENCHMARK}>:PONY_ENGINE_TESTING_BENCHMARK>
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Surface.Tests PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Setting build options")
pony_set_build_options(PonyEngine.Surface.Tests ${PONY_ENGINE_OPTIMIZATION})

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Surface.Tests PRIVATE 
	Catch2::Catch2WithMain
	PonyEngine.Core
	PonyEngine.Surface
)

message(VERBOSE "Discovering tests")
catch_discover_tests(PonyEngine.Surface.Tests)
