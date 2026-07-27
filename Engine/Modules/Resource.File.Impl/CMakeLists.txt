message(STATUS "Configuring PonyEngine.Resource.File.Impl")

message(VERBOSE "Configuring parameters")
set(PONY_ENGINE_RESOURCE_FILE_ORDER "p" CACHE STRING "PonyEngine.Resource.File.Impl module initialization order. Its first character must be in range [b-y].")
set(PONY_ENGINE_RESOURCE_FILE_MANIFEST_DIR "Manifests/Resource/File" CACHE STRING "File resource manifest directory. It must be relative to a root directory.")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Resource.File.Impl STATIC)

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.Resource.File.Impl PUBLIC
	"Include/Public"
)

message(VERBOSE "Configuring sources")
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

message(VERBOSE "Configuring defines")
pony_validate_module_order(PONY_ENGINE_RESOURCE_FILE_ORDER)
pony_validate_path(PONY_ENGINE_RESOURCE_FILE_MANIFEST_DIR CAN_BE_RELATIVE)
target_compile_definitions(PonyEngine.Resource.File.Impl PUBLIC
	PONY_ENGINE_RESOURCE_FILE_ORDER=${PONY_ENGINE_RESOURCE_FILE_ORDER}
	PONY_ENGINE_RESOURCE_FILE_MANIFEST_DIR=${PONY_ENGINE_RESOURCE_FILE_MANIFEST_DIR}
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Resource.File.Impl PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
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
