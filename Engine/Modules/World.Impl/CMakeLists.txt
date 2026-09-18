message(STATUS "Configuring PonyEngine.World.Impl feature module")

set(PONY_ENGINE_WORLD_ORDER "p" CACHE STRING "PonyEngine.World.Impl module initialization order. Its first character must be in range [b-y].")

add_library(PonyEngine.World.Impl STATIC)

target_include_directories(PonyEngine.World.Impl PUBLIC
	"Include/Public"
)

target_sources(PonyEngine.World.Impl PUBLIC
	"Source/Launch.cpp"
)
target_sources(PonyEngine.World.Impl PRIVATE
	"Source/Launch.Impl.cpp"
)
target_sources(PonyEngine.World.Impl PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/World.cppm"
	"Source/World-ComponentTable.cppm"
	"Source/World-ObjectTable.cppm"
	"Source/World-TypeRegistry.cppm"
	"Source/World-World.cppm"
	"Source/World-WorldService.cppm"
	"Source/World-WorldServiceModule.cppm"
)

pony_validate_module_order(PONY_ENGINE_WORLD_ORDER)
target_compile_definitions(PonyEngine.World.Impl PUBLIC
	PONY_ENGINE_WORLD_ORDER=${PONY_ENGINE_WORLD_ORDER}
)

set_target_properties(PonyEngine.World.Impl PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.World.Impl PUBLIC
	PonyEngine.Application
)
target_link_libraries(PonyEngine.World.Impl PRIVATE
	PonyEngine.Core
	PonyEngine.Log
	PonyEngine.World
)
