message(STATUS "Configuring PonyEngine.Resource.File.Impl")

set(PONY_ENGINE_RESOURCE_FILE_ORDER "p" CACHE STRING "PonyEngine.Resource.File.Impl module initialization order. Its first character must be in range [b-y].")
set(PONY_ENGINE_RESOURCE_FILE_MANIFEST_DIR "Manifests/Resource/File" CACHE STRING "File resource manifest directory. It must be relative to a root directory.")

add_library(PonyEngine.Resource.File.Impl STATIC)

target_include_directories(PonyEngine.Resource.File.Impl PUBLIC
	"Include/Public"
)

target_sources(PonyEngine.Resource.File.Impl PUBLIC
	"Source/Launch.cpp"
)
target_sources(PonyEngine.Resource.File.Impl PRIVATE
	"Source/Launch.Impl.cpp"
)
target_sources(PonyEngine.Resource.File.Impl PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Main.cppm"
	"Source/Main-FileResourceData.cppm"
	"Source/Main-FileResourceProvider.cppm"
	"Source/Main-FileResourceProviderModule.cppm"
	"Source/Main-LoadableResourceData.cppm"
	"Source/Main-LoadRequest.cppm"
	"Source/Main-LoadRequestManager.cppm"
)

pony_validate_module_order(PONY_ENGINE_RESOURCE_FILE_ORDER)
pony_validate_path(PONY_ENGINE_RESOURCE_FILE_MANIFEST_DIR CAN_BE_RELATIVE)
target_compile_definitions(PonyEngine.Resource.File.Impl PUBLIC
	PONY_ENGINE_RESOURCE_FILE_ORDER=${PONY_ENGINE_RESOURCE_FILE_ORDER}
)
target_compile_definitions(PonyEngine.Resource.File.Impl PRIVATE
	PONY_ENGINE_RESOURCE_FILE_MANIFEST_DIR=${PONY_ENGINE_RESOURCE_FILE_MANIFEST_DIR}
)

set_target_properties(PonyEngine.Resource.File.Impl PROPERTIES
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
target_link_libraries(PonyEngine.Resource.File.Impl PUBLIC
	PonyEngine.Application
)
target_link_libraries(PonyEngine.Resource.File.Impl PRIVATE
	PonyEngine.Resource
	PonyEngine.Resource.Ext
	PonyEngine.Core
	PonyEngine.Log
	PonyEngine.File
)
