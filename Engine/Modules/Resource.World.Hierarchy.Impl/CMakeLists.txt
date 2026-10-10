message(STATUS "Configuring PonyEngine.Resource.World.Hierarchy.Impl feature module")

set(PONY_ENGINE_RESOURCE_WORLD_HIERARCHY_ORDER "p" CACHE STRING "PonyEngine.Resource.World.Hierarchy.Impl module initialization order. Its first character must be in range [b-y].")

add_library(PonyEngine.Resource.World.Hierarchy.Impl STATIC)

target_include_directories(PonyEngine.Resource.World.Hierarchy.Impl PUBLIC
	"Include/Public"
)

target_sources(PonyEngine.Resource.World.Hierarchy.Impl PUBLIC
	"Source/Launch.cpp"
)
target_sources(PonyEngine.Resource.World.Hierarchy.Impl PRIVATE
	"Source/Launch.Impl.cpp"
)
target_sources(PonyEngine.Resource.World.Hierarchy.Impl PRIVATE FILE_SET CXX_MODULES FILES
	"Source/Hierarchy.cppm"
	"Source/Hierarchy-HierarchyDeserializerModule.cppm"
)

pony_validate_module_order(PONY_ENGINE_RESOURCE_WORLD_HIERARCHY_ORDER)
target_compile_definitions(PonyEngine.Resource.World.Hierarchy.Impl PUBLIC
	PONY_ENGINE_RESOURCE_WORLD_HIERARCHY_ORDER=${PONY_ENGINE_RESOURCE_WORLD_HIERARCHY_ORDER}
)

set_target_properties(PonyEngine.Resource.World.Hierarchy.Impl PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.Resource.World.Hierarchy.Impl PUBLIC
	PonyEngine.Application
)
target_link_libraries(PonyEngine.Resource.World.Hierarchy.Impl PRIVATE
	PonyEngine.Core
	PonyEngine.Resource.World
	PonyEngine.World.Hierarchy
)
