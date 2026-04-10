message(STATUS "Configuring PonyEngine.RawInput.Tests")
add_executable(PonyEngine.RawInput.Tests)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.RawInput.Tests PRIVATE
	"RawInput/Axis.cpp"
	"RawInput/DeviceType.cpp"
	"RawInput/Gamepad.cpp"
	"RawInput/Keyboard.cpp" 
	"RawInput/Layout.cpp"
	"RawInput/Mouse.cpp"
)

message(VERBOSE "Configuring defines")
pony_set_log_defines(PonyEngine.RawInput.Tests ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL})
target_compile_definitions(PonyEngine.RawInput.Tests PRIVATE 
	$<$<BOOL:${PONY_ENGINE_TESTING_BENCHMARK}>:PONY_ENGINE_TESTING_BENCHMARK>
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.RawInput.Tests PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Setting build options")
pony_set_build_options(PonyEngine.RawInput.Tests ${PONY_ENGINE_OPTIMIZATION})

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.RawInput.Tests PRIVATE 
	Catch2::Catch2WithMain
	PonyEngine.RawInput
	PonyEngine.Core
)

message(VERBOSE "Discovering tests")
catch_discover_tests(PonyEngine.RawInput.Tests)
