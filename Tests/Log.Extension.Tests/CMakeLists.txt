message(STATUS "Configuring PonyEngine.Log.Extension.Tests")
add_executable(PonyEngine.Log.Extension.Tests)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Log.Extension.Tests PRIVATE
	"Log/LogEntry.cpp"
)

message(VERBOSE "Configuring defines")
pony_set_log_defines(PonyEngine.Log.Extension.Tests ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL} ${PONY_CONSOLE_LOG} ${PONY_PLATFORM_CONSOLE_LOG})

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Log.Extension.Tests PROPERTIES 
	CXX_STANDARD 23
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Setting build options")
pony_set_build_options(PonyEngine.Log.Extension.Tests ${PONY_ENGINE_OPTIMIZATION})

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Log.Extension.Tests PRIVATE 
	Catch2::Catch2WithMain
	PonyEngine.Core
	PonyEngine.Log.Extension
)

message(VERBOSE "Discovering tests")
catch_discover_tests(PonyEngine.Log.Extension.Tests)
