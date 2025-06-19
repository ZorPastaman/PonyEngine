message(STATUS "Configuring PonyEngine.Log.Extension.Tests")
add_executable(PonyEngine.Log.Extension.Tests)

message(STATUS "Configuring sources")
target_sources(PonyEngine.Log.Extension.Tests PRIVATE
	"Log/LogEntry.cpp"
)

message(STATUS "Configuring defines")
pony_set_log_defines(PonyEngine.Log.Extension.Tests ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL} ${PONY_CONSOLE_LOG} ${PONY_PLATFORM_CONSOLE_LOG})

message(STATUS "Setting properties")
set_target_properties(PonyEngine.Log.Extension.Tests PROPERTIES CXX_STANDARD 23)

message(STATUS "Setting build options")
pony_set_build_options(PonyEngine.Log.Extension.Tests ${PONY_ENGINE_OPTIMIZATION})

message(STATUS "Configuring dependencies")
target_link_libraries(PonyEngine.Log.Extension.Tests PRIVATE 
	Catch2::Catch2WithMain
	PonyEngine.Core
	PonyEngine.Log.Extension
)

message(STATUS "Discovering tests")
include(CTest)
include(Catch)
catch_discover_tests(PonyEngine.Log.Extension.Tests)
