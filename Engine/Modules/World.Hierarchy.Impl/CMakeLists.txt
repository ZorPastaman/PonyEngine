message(STATUS "Configuring PonyEngine.World.Hierarchy.Impl feature module")

set(PONY_ENGINE_WORLD_HIERARCHY_ORDER "p" CACHE STRING "PonyEngine.World.Hierarchy.Impl module initialization order. Its first character must be in range [b-y].")

add_library(PonyEngine.World.Hierarchy.Impl STATIC)

target_sources(PonyEngine.World.Hierarchy.Impl PUBLIC
	"Source/Launch.cpp"
)
target_sources(PonyEngine.World.Hierarchy.Impl PRIVATE
	"Source/Launch.Impl.cpp"
)
target_sources(PonyEngine.World.Hierarchy.Impl PRIVATE FILE_SET CXX_MODULES FILES
	"Source/Hierarchy.cppm"
	"Source/Hierarchy-HierarchyService.cppm"
)

pony_validate_module_order(PONY_ENGINE_WORLD_HIERARCHY_ORDER)
target_compile_definitions(PonyEngine.Time.Impl PUBLIC
	PONY_ENGINE_WORLD_HIERARCHY_ORDER=${PONY_ENGINE_WORLD_HIERARCHY_ORDER}
)

set_target_properties(PonyEngine.World.Hierarchy.Impl PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.World.Hierarchy.Impl PUBLIC
	PonyEngine.Application
)
target_link_libraries(PonyEngine.World.Hierarchy.Impl PRIVATE
	PonyEngine.Core
	PonyEngine.Log
	PonyEngine.World
	PonyEngine.World.Hierarchy
)
