message(STATUS "Configuring PonyEngine.Log.Tests")
add_executable(PonyEngine.Log.Tests)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Log.Tests PRIVATE
	"Log/LogFormat.cpp"
	"Log/LogMacro.cpp"
)

message(VERBOSE "Configuring defines")
pony_set_log_defines(PonyEngine.Log.Tests ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL} ${PONY_CONSOLE_LOG} ${PONY_PLATFORM_CONSOLE_LOG})
if(PONY_ENGINE_TESTING_BENCHMARK)
	target_compile_definitions(PonyEngine.Log.Tests PRIVATE PONY_ENGINE_TESTING_BENCHMARK)
endif()

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Log.Tests PROPERTIES 
	CXX_STANDARD 23
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Setting build options")
pony_set_build_options(PonyEngine.Log.Tests ${PONY_ENGINE_OPTIMIZATION})
target_compile_definitions(PonyEngine.Core.Tests PRIVATE 
	$<$<BOOL:${PONY_ENGINE_TESTING_BENCHMARK}>:PONY_ENGINE_TESTING_BENCHMARK>
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Log.Tests PRIVATE 
	Catch2::Catch2WithMain
	PonyEngine.Log
	PonyEngine.Core
	PonyEngine.Application.Extension
)

message(VERBOSE "Discovering tests")
catch_discover_tests(PonyEngine.Log.Tests)
