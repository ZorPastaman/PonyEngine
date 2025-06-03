message(STATUS "Configuring PonyEngine.Log.Tests")
add_executable(PonyEngine.Log.Tests)

message(STATUS "Configuring sources")
target_sources(PonyEngine.Log.Tests PRIVATE
	"Log/LogFormat.cpp"
 "Log/LogHelper.cpp")

message(STATUS "Configuring dependencies")
target_link_libraries(PonyEngine.Log.Tests PRIVATE 
	Catch2::Catch2WithMain
	PonyEngine.Log
)

message(STATUS "Discovering tests")
include(CTest)
include(Catch)
catch_discover_tests(PonyEngine.Log.Tests)
