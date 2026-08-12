message(STATUS "Configuring PonyEngine.Resource.Impl")

if(NOT TARGET PonyEngine.Application)
	message(FATAL_ERROR "PonyEngine.Application wasn't configured")
endif()
if(NOT TARGET PonyEngine.Core)
	message(FATAL_ERROR "PonyEngine.Core wasn't configured")
endif()
if(NOT TARGET PonyEngine.Log)
	message(FATAL_ERROR "PonyEngine.Log wasn't configured")
endif()
if(NOT TARGET PonyEngine.Resource)
	message(FATAL_ERROR "PonyEngine.Resource wasn't configured")
endif()
if(NOT TARGET PonyEngine.Resource.Ext)
	message(FATAL_ERROR "PonyEngine.Resource.Ext wasn't configured")
endif()

set(PONY_ENGINE_RESOURCE_ORDER "p" CACHE STRING "PonyEngine.Resource.Impl module initialization order. Its first character must be in range [b-y].")
set(PONY_ENGINE_RESOURCE_TICK_ORDER "0" CACHE STRING "PonyEngine.Resource.Impl service tick order. It must be an int32 number.")

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
	"Source/Main.cppm"
	"Source/Main-CachedResourceRequest.cppm"
	"Source/Main-CollectionContainer.cppm"
	"Source/Main-LoadableResource.cppm"
	"Source/Main-LoaderContainer.cppm"
	"Source/Main-Resource.cppm"
	"Source/Main-ResourceCache.cppm"
	"Source/Main-ResourceContainer.cppm"
	"Source/Main-ResourceService.cppm"
	"Source/Main-ResourceServiceModule.cppm"
)

pony_validate_module_order(PONY_ENGINE_RESOURCE_ORDER)
pony_validate_tick_order(PONY_ENGINE_RESOURCE_TICK_ORDER)
target_compile_definitions(PonyEngine.Resource.Impl PUBLIC
	PONY_ENGINE_RESOURCE_ORDER=${PONY_ENGINE_RESOURCE_ORDER}
)
target_compile_definitions(PonyEngine.Resource.Impl PRIVATE
	PONY_ENGINE_RESOURCE_TICK_ORDER=${PONY_ENGINE_RESOURCE_TICK_ORDER}
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
