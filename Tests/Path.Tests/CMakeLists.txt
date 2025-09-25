message(STATUS "Configuring PonyEngine.Path.Tests")
add_executable(PonyEngine.Path.Tests)

if (PONY_WINDOWS)
	message(VERBOSE "Configuring sources for Windows")
	target_sources(PonyEngine.Path.Tests PRIVATE
		"Path/Windows/Utility.cpp"
	)
endif()

message(VERBOSE "Configuring defines")
pony_set_log_defines(PonyEngine.Path.Tests ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL} ${PONY_CONSOLE_LOG} ${PONY_PLATFORM_CONSOLE_LOG})

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Path.Tests PROPERTIES 
	CXX_STANDARD 23
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Setting build options")
pony_set_build_options(PonyEngine.Path.Tests ${PONY_ENGINE_OPTIMIZATION})

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Path.Tests PRIVATE 
	Catch2::Catch2WithMain
	PonyEngine.Core
	PonyEngine.Path
)

message(VERBOSE "Discovering tests")
catch_discover_tests(PonyEngine.Path.Tests)
