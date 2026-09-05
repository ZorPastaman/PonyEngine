message(STATUS "Configuring PonyEngine.Resource.Pack.Impl feature module")

set(PONY_ENGINE_RESOURCE_PACK_ORDER "p" CACHE STRING "PonyEngine.Resource.Pack.Impl module initialization order. Its first character must be in range [b-y].")

add_library(PonyEngine.Resource.Pack.Impl STATIC)

target_include_directories(PonyEngine.Resource.Pack.Impl PUBLIC
	"Include/Public"
)

target_sources(PonyEngine.Resource.Pack.Impl PUBLIC
	"Source/Launch.cpp"
)
target_sources(PonyEngine.Resource.Pack.Impl PRIVATE
	"Source/Launch.Impl.cpp"
)
target_sources(PonyEngine.Resource.Pack.Impl PRIVATE FILE_SET CXX_MODULES FILES
	"Source/Pack.cppm"
	"Source/Pack-DataAccessWorker.cppm"
	"Source/Pack-FileDataAccess.cppm"
	"Source/Pack-FileLoadableDataAccess.cppm"
	"Source/Pack-FileLoadableDataAccessRequest.cppm"
	"Source/Pack-FilePackMountRequest.cppm"
	"Source/Pack-LoadableDataAccessRequest.cppm"
	"Source/Pack-LoadableDataAccessRequestWorker.cppm"
	"Source/Pack-MemoryDataAccess.cppm"
	"Source/Pack-MemoryLoadableDataAccess.cppm"
	"Source/Pack-Pack.cppm"
	"Source/Pack-PackContainer.cppm"
	"Source/Pack-PackMountRequest.cppm"
	"Source/Pack-PackService.cppm"
	"Source/Pack-PackServiceModule.cppm"
	"Source/Pack-PackUnmountRequest.cppm"
)

pony_validate_module_order(PONY_ENGINE_RESOURCE_PACK_ORDER)
target_compile_definitions(PonyEngine.Resource.Pack.Impl PUBLIC
	PONY_ENGINE_RESOURCE_PACK_ORDER=${PONY_ENGINE_RESOURCE_PACK_ORDER}
)

set_target_properties(PonyEngine.Resource.Pack.Impl PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.Resource.Pack.Impl PUBLIC
	PonyEngine.Application
)
target_link_libraries(PonyEngine.Resource.Pack.Impl PRIVATE
	PonyEngine.Core
	PonyEngine.File
	PonyEngine.Job
	PonyEngine.Log
	PonyEngine.Resource
	PonyEngine.Resource.Ext
	PonyEngine.Resource.Pack
)
