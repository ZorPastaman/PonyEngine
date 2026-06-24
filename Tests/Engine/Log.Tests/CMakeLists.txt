message(STATUS "Configuring PonyEngine.Log.Tests")
add_executable(PonyEngine.Log.Tests)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Log.Tests PRIVATE
	"Log/LogMacro.cpp"
	"Log/LogMacroStacktrace.cpp"
)

message(VERBOSE "Configuring defines")
pony_set_log_defines(PonyEngine.Log.Tests ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL})
target_compile_definitions(PonyEngine.Log.Tests PRIVATE 
	$<$<BOOL:${PONY_ENGINE_TESTING_BENCHMARK}>:PONY_ENGINE_TESTING_BENCHMARK>
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Log.Tests PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Setting build options")
pony_set_build_options(PonyEngine.Log.Tests ${PONY_ENGINE_OPTIMIZATION})

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Log.Tests PRIVATE 
	Catch2::Catch2WithMain
	PonyEngine.Log
	PonyEngine.Core
	PonyEngine.Application.Ext
)

message(VERBOSE "Discovering tests")
catch_discover_tests(PonyEngine.Log.Tests)
