message(STATUS "Configuring PonyEngine.Resource.World.Impl feature module")

set(PONY_ENGINE_RESOURCE_WORLD_ORDER "p" CACHE STRING "PonyEngine.Resource.World.Impl module initialization order. Its first character must be in range [b-y].")

add_library(PonyEngine.Resource.World.Impl STATIC)

target_include_directories(PonyEngine.Resource.World.Impl PUBLIC
	"Include/Public"
)

target_sources(PonyEngine.Resource.World.Impl PUBLIC
	"Source/Launch.cpp"
)
target_sources(PonyEngine.Resource.World.Impl PRIVATE
	"Source/Launch.Impl.cpp"
)
target_sources(PonyEngine.Resource.World.Impl PRIVATE FILE_SET CXX_MODULES FILES
	"Source/World.cppm"
	"Source/World-CopyComponentDeserializer.cppm"
	"Source/World-LoadableWorldDefinitionLoadRequest.cppm"
	"Source/World-WorldDefinitionLoader.cppm"
	"Source/World-WorldDefinitionLoaderModule.cppm"
	"Source/World-WorldDefinitionLoadRequest.cppm"
)

pony_validate_module_order(PONY_ENGINE_RESOURCE_WORLD_ORDER)
target_compile_definitions(PonyEngine.Resource.World.Impl PUBLIC
	PONY_ENGINE_RESOURCE_WORLD_ORDER=${PONY_ENGINE_RESOURCE_WORLD_ORDER}
)

set_target_properties(PonyEngine.Resource.World.Impl PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.Resource.World.Impl PUBLIC
	PonyEngine.Application
)
target_link_libraries(PonyEngine.Resource.World.Impl PRIVATE
	PonyEngine.Core
	PonyEngine.Job
	PonyEngine.Log
	PonyEngine.Resource
	PonyEngine.Resource.Ext
	PonyEngine.Resource.World
	PonyEngine.World
)
