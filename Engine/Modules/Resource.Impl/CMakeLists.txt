message(STATUS "Configuring PonyEngine.Resource.Impl")

message(VERBOSE "Configuring parameters")
set(PONY_ENGINE_RESOURCE_ORDER "p" CACHE STRING "PonyEngine.Resource.Impl module initialization order. Its first character must be in range [b-y].")
set(PONY_ENGINE_RESOURCE_TICK_ORDER "0" CACHE STRING "PonyEngine.Resource.Impl service tick order. It must be an int32 number.")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Resource.Impl STATIC)

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.Resource.Impl PUBLIC
	"Include/Public"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Resource.Impl PUBLIC
	"Source/Launch.cpp"
)
target_sources(PonyEngine.Resource.Impl PRIVATE
	"Source/Launch.Impl.cpp"
)
target_sources(PonyEngine.Resource.Impl PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Main.cppm"
	"Source/Main-FileResource.cppm"
	"Source/Main-LoadableResource.cppm"
	"Source/Main-MemoryResource.cppm"
	"Source/Main-ResourceContainer.cppm"
	"Source/Main-ResourceEntry.cppm"
	"Source/Main-ResourceProviderContainer.cppm"
	"Source/Main-ResourceService.cppm"
	"Source/Main-ResourceServiceModule.cppm"
	"Source/Main-VariantEntry.cppm"
)

message(VERBOSE "Configuring defines")
pony_validate_module_order(PONY_ENGINE_RESOURCE_ORDER)
pony_validate_tick_order(PONY_ENGINE_RESOURCE_TICK_ORDER)
target_compile_definitions(PonyEngine.Resource.Impl PUBLIC
	PONY_ENGINE_RESOURCE_ORDER=${PONY_ENGINE_RESOURCE_ORDER}
	PONY_ENGINE_RESOURCE_TICK_ORDER=${PONY_ENGINE_RESOURCE_TICK_ORDER}
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Resource.Impl PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
if(NOT TARGET PonyEngine.Resource)
	message(FATAL_ERROR "PonyEngine.Resource wasn't configured")
endif()
if(NOT TARGET PonyEngine.Resource.Ext)
	message(FATAL_ERROR "PonyEngine.Resource.Ext wasn't configured")
endif()
target_link_libraries(PonyEngine.Resource.Impl PUBLIC
	PonyEngine.Application.Ext
)
target_link_libraries(PonyEngine.Resource.Impl PRIVATE
	PonyEngine.Resource
	PonyEngine.Resource.Ext
	PonyEngine.Core
	PonyEngine.Log
)
