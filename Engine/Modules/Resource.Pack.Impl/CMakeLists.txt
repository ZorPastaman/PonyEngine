message(STATUS "Configuring PonyEngine.Resource.Pack.Impl")

set(PONY_ENGINE_RESOURCE_PACK_ORDER "p" CACHE STRING "PonyEngine.Resource.Pack.Impl module initialization order. Its first character must be in range [b-y].")
set(PONY_ENGINE_RESOURCE_PACK_MANIFEST_DIR "Manifests/Resource/Pack" CACHE STRING "Pack resource manifest directory. It must be relative to a root directory.")

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
	"Source/Main-FileResourceData.cppm"
	"Source/Main-LoadableResourceData.cppm"
	"Source/Main-LoadRequest.cppm"
	"Source/Main-LoadRequestManager.cppm"
	"Source/Main-PackResourceProvider.cppm"
	"Source/Main-PackResourceProviderModule.cppm"
)

pony_validate_module_order(PONY_ENGINE_RESOURCE_PACK_ORDER)
pony_validate_path(PONY_ENGINE_RESOURCE_PACK_MANIFEST_DIR CAN_BE_RELATIVE)
target_compile_definitions(PonyEngine.Resource.Pack.Impl PUBLIC
	PONY_ENGINE_RESOURCE_PACK_ORDER=${PONY_ENGINE_RESOURCE_PACK_ORDER}
)
target_compile_definitions(PonyEngine.Resource.Pack.Impl PRIVATE
	PONY_ENGINE_RESOURCE_PACK_MANIFEST_DIR=${PONY_ENGINE_RESOURCE_PACK_MANIFEST_DIR}
)

set_target_properties(PonyEngine.Resource.Pack.Impl PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

if(NOT TARGET PonyEngine.Resource)
	message(FATAL_ERROR "PonyEngine.Resource wasn't configured")
endif()
if(NOT TARGET PonyEngine.Resource.Ext)
	message(FATAL_ERROR "PonyEngine.Resource.Ext wasn't configured")
endif()
if(NOT TARGET PonyEngine.File)
	message(FATAL_ERROR "PonyEngine.File wasn't configured")
endif()
target_link_libraries(PonyEngine.Resource.Pack.Impl PUBLIC
	PonyEngine.Application
)
target_link_libraries(PonyEngine.Resource.Pack.Impl PRIVATE
	PonyEngine.Resource
	PonyEngine.Resource.Ext
	PonyEngine.Core
	PonyEngine.Log
	PonyEngine.File
)
