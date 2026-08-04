message(STATUS "Configuring PonyEngine.Resource.Ext")

add_library(PonyEngine.Resource.Ext STATIC)

target_sources(PonyEngine.Resource.Ext PUBLIC FILE_SET CXX_MODULES FILES 
	"Source/Main.cppm"
	"Source/Main-IFileResourceData.cppm"
	"Source/Main-ILoadableResourceData.cppm"
	"Source/Main-IMemoryResourceData.cppm"
	"Source/Main-IResourceContext.cppm"
	"Source/Main-IResourceModuleContext.cppm"
	"Source/Main-IResourceProvider.cppm"
	"Source/Main-IResourceRegistry.cppm"
	"Source/Main-ResourceHandle.cppm"
	"Source/Main-ResourceParams.cppm"
	"Source/Main-ResourceProviderHandle.cppm"
)

set_target_properties(PonyEngine.Resource.Ext PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

if(NOT TARGET PonyEngine.Resource)
	message(FATAL_ERROR "PonyEngine.Resource wasn't configured")
endif()
target_link_libraries(PonyEngine.Resource.Ext PUBLIC
	PonyEngine.Resource
	PonyEngine.Core
	PonyEngine.Application
	PonyEngine.Log
)
