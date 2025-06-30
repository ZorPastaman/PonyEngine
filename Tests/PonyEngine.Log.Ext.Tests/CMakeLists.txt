message(STATUS "Configuring PonyEngine.Log.Ext.Tests")
add_executable(PonyEngine.Log.Ext.Tests)

message(STATUS "Configuring sources")
target_sources(PonyEngine.Log.Ext.Tests PRIVATE
	"Log/LogEntry.cpp"
)

message(STATUS "Configuring defines")
pony_set_log_defines(PonyEngine.Log.Ext.Tests ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL} ${PONY_CONSOLE_LOG} ${PONY_PLATFORM_CONSOLE_LOG})

message(STATUS "Setting properties")
set_target_properties(PonyEngine.Log.Ext.Tests PROPERTIES CXX_STANDARD 23)

message(STATUS "Setting build options")
pony_set_build_options(PonyEngine.Log.Ext.Tests ${PONY_ENGINE_OPTIMIZATION})

message(STATUS "Configuring dependencies")
target_link_libraries(PonyEngine.Log.Ext.Tests PRIVATE 
	Catch2::Catch2WithMain
	PonyEngine.Core
	PonyEngine.Log.Ext
)

message(STATUS "Discovering tests")
include(CTest)
include(Catch)
catch_discover_tests(PonyEngine.Log.Ext.Tests)
