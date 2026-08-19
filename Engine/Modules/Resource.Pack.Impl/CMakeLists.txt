message(STATUS "Configuring PonyEngine.Resource.Pack.Impl")

if(NOT TARGET PonyEngine.Application)
	message(FATAL_ERROR "PonyEngine.Application wasn't configured")
endif()
if(NOT TARGET PonyEngine.Core)
	message(FATAL_ERROR "PonyEngine.Core wasn't configured")
endif()
if(NOT TARGET PonyEngine.File)
	message(FATAL_ERROR "PonyEngine.File wasn't configured")
endif()
if(NOT TARGET PonyEngine.Job)
	message(FATAL_ERROR "PonyEngine.Job wasn't configured")
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
if(NOT TARGET PonyEngine.Resource.Pack)
	message(FATAL_ERROR "PonyEngine.Resource.Pack wasn't configured")
endif()

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
	"Source/Main.cppm"
	"Source/Main-FileDataAccess.cppm"
	"Source/Main-FileLoadableDataAccess.cppm"
	"Source/Main-FileLoadableDataAccessRequest.cppm"
	"Source/Main-LoadableDataAccessRequestBuffer.cppm"
	"Source/Main-MemoryDataAccess.cppm"
	"Source/Main-Pack.cppm"
	"Source/Main-PackContainer.cppm"
	"Source/Main-PackService.cppm"
	"Source/Main-PackServiceModule.cppm"
 "Source/Main-MemoryLoadableDataAccessRequest.cppm" "Source/Main-MemoryLoadableDataAccess.cppm")

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
