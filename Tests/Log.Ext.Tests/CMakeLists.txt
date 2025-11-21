message(STATUS "Configuring PonyEngine.Log.Ext.Tests")
add_executable(PonyEngine.Log.Ext.Tests)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Log.Ext.Tests PRIVATE
	"Log/ConsoleMacro.cpp"
 "Log/ConsoleMacroStacktrace.cpp")

message(VERBOSE "Configuring defines")
pony_set_log_defines(PonyEngine.Log.Ext.Tests ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL})

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Log.Ext.Tests PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Setting build options")
pony_set_build_options(PonyEngine.Log.Ext.Tests ${PONY_ENGINE_OPTIMIZATION})
target_compile_definitions(PonyEngine.Core.Tests PRIVATE 
	$<$<BOOL:${PONY_ENGINE_TESTING_BENCHMARK}>:PONY_ENGINE_TESTING_BENCHMARK>
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Log.Ext.Tests PRIVATE 
	Catch2::Catch2WithMain
	PonyEngine.Core
	PonyEngine.Log.Ext
)

message(VERBOSE "Discovering tests")
catch_discover_tests(PonyEngine.Log.Ext.Tests)
