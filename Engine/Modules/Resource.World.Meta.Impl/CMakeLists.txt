message(STATUS "Configuring PonyEngine.Resource.World.Meta.Impl feature module")

set(PONY_ENGINE_RESOURCE_WORLD_META_ORDER "p" CACHE STRING "PonyEngine.Resource.World.Meta.Impl module initialization order. Its first character must be in range [b-y].")

add_library(PonyEngine.Resource.World.Meta.Impl STATIC)

target_include_directories(PonyEngine.Resource.World.Meta.Impl PUBLIC
	"Include/Public"
)

target_sources(PonyEngine.Resource.World.Meta.Impl PUBLIC
	"Source/Launch.cpp"
)
target_sources(PonyEngine.Resource.World.Meta.Impl PRIVATE
	"Source/Launch.Impl.cpp"
)
target_sources(PonyEngine.Resource.World.Meta.Impl PRIVATE FILE_SET CXX_MODULES FILES
	"Source/Meta.cppm"
	"Source/Meta-MetaDeserializerModule.cppm"
	"Source/Meta-NameDeserializer.cppm"
)

pony_validate_module_order(PONY_ENGINE_RESOURCE_WORLD_META_ORDER)
target_compile_definitions(PonyEngine.Resource.World.Meta.Impl PUBLIC
	PONY_ENGINE_RESOURCE_WORLD_META_ORDER=${PONY_ENGINE_RESOURCE_WORLD_META_ORDER}
)

set_target_properties(PonyEngine.Resource.World.Meta.Impl PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.Resource.World.Meta.Impl PUBLIC
	PonyEngine.Application
)
target_link_libraries(PonyEngine.Resource.World.Meta.Impl PRIVATE
	PonyEngine.Core
	PonyEngine.Resource.World.Ext
	PonyEngine.World.Meta
)
