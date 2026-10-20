message(STATUS "Configuring PonyEngine.World.Meta.Impl feature module")

set(PONY_ENGINE_WORLD_META_ORDER "p" CACHE STRING "PonyEngine.World.Meta.Impl module initialization order. Its first character must be in range [b-y].")

add_library(PonyEngine.World.Meta.Impl STATIC)

target_include_directories(PonyEngine.World.Meta.Impl PUBLIC
	"Include/Public"
)

target_sources(PonyEngine.World.Meta.Impl PUBLIC
	"Source/Launch.cpp"
)
target_sources(PonyEngine.World.Meta.Impl PRIVATE
	"Source/Launch.Impl.cpp"
)
target_sources(PonyEngine.World.Meta.Impl PRIVATE FILE_SET CXX_MODULES FILES
	"Source/Meta.cppm"
	"Source/Meta-MetaModule.cppm"
)

pony_validate_module_order(PONY_ENGINE_WORLD_META_ORDER)
target_compile_definitions(PonyEngine.World.Meta.Impl PUBLIC
	PONY_ENGINE_WORLD_META_ORDER=${PONY_ENGINE_WORLD_META_ORDER}
)

set_target_properties(PonyEngine.World.Meta.Impl PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.World.Meta.Impl PUBLIC
	PonyEngine.Application
)
target_link_libraries(PonyEngine.World.Meta.Impl PRIVATE
	PonyEngine.Core
	PonyEngine.World
	PonyEngine.World.Meta
)
