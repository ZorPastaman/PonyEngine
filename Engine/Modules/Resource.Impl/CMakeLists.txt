message(STATUS "Configuring PonyEngine.Resource.Impl feature module")

set(PONY_ENGINE_RESOURCE_ORDER "p" CACHE STRING "PonyEngine.Resource.Impl module initialization order. Its first character must be in range [b-y].")

add_library(PonyEngine.Resource.Impl STATIC)

target_include_directories(PonyEngine.Resource.Impl PUBLIC
	"Include/Public"
)

target_sources(PonyEngine.Resource.Impl PUBLIC
	"Source/Launch.cpp"
)
target_sources(PonyEngine.Resource.Impl PRIVATE
	"Source/Launch.Impl.cpp"
)
target_sources(PonyEngine.Resource.Impl PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Resource.cppm"
	"Source/Resource-CollectionContainer.cppm"
	"Source/Resource-CompletedResourceRequest.cppm"
	"Source/Resource-LoadableResource.cppm"
	"Source/Resource-LoaderContainer.cppm"
	"Source/Resource-Resource.cppm"
	"Source/Resource-ResourceContainer.cppm"
	"Source/Resource-ResourceLoadProcess.cppm"
	"Source/Resource-ResourceService.cppm"
	"Source/Resource-ResourceServiceModule.cppm"
	"Source/Resource-Utility.cppm"
)

pony_validate_module_order(PONY_ENGINE_RESOURCE_ORDER)
target_compile_definitions(PonyEngine.Resource.Impl PUBLIC
	PONY_ENGINE_RESOURCE_ORDER=${PONY_ENGINE_RESOURCE_ORDER}
)

set_target_properties(PonyEngine.Resource.Impl PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.Resource.Impl PUBLIC
	PonyEngine.Application
)
target_link_libraries(PonyEngine.Resource.Impl PRIVATE
	PonyEngine.Core
	PonyEngine.Log
	PonyEngine.Resource
	PonyEngine.Resource.Ext
)
