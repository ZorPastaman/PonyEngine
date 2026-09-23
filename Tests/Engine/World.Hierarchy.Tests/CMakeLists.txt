message(STATUS "Configuring PonyEngine.World.Hierarchy.Tests")
add_executable(PonyEngine.World.Hierarchy.Tests)

target_sources(PonyEngine.World.Hierarchy.Tests PRIVATE
	"Hierarchy/LocalTransform.cpp"
)

target_compile_definitions(PonyEngine.World.Hierarchy.Tests PRIVATE 
	$<$<BOOL:${PONY_ENGINE_TESTING_BENCHMARK}>:PONY_ENGINE_TESTING_BENCHMARK>
)

target_link_libraries(PonyEngine.World.Hierarchy.Tests PRIVATE 
	Catch2::Catch2WithMain
	PonyEngine.Core
	PonyEngine.World.Hierarchy
)

catch_discover_tests(PonyEngine.World.Hierarchy.Tests)
