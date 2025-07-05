message(STATUS "Configuring PonyEngine.Math.Tests")
add_executable(PonyEngine.Math.Tests)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Math.Tests PRIVATE
	"Math/Common.cpp"
)

message(VERBOSE "Configuring defines")
pony_set_log_defines(PonyEngine.Math.Tests ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL} ${PONY_CONSOLE_LOG} ${PONY_PLATFORM_CONSOLE_LOG})
if(PONY_ENGINE_TESTING_BENCHMARK)
	target_compile_definitions(PonyEngine.Math.Tests PRIVATE PONY_ENGINE_TESTING_BENCHMARK)
endif()

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Math.Tests PROPERTIES 
	CXX_STANDARD 23
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Setting build options")
pony_set_build_options(PonyEngine.Math.Tests ${PONY_ENGINE_OPTIMIZATION})

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Math.Tests PRIVATE 
	Catch2::Catch2WithMain
	PonyEngine.Math
)

message(VERBOSE "Discovering tests")
catch_discover_tests(PonyEngine.Math.Tests)
