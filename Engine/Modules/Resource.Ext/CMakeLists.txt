message(STATUS "Configuring PonyEngine.Resource.Ext")

if(NOT TARGET PonyEngine.Core)
	message(FATAL_ERROR "PonyEngine.Core wasn't configured")
endif()
if(NOT TARGET PonyEngine.Resource)
	message(FATAL_ERROR "PonyEngine.Resource wasn't configured")
endif()

add_library(PonyEngine.Resource.Ext STATIC)

target_sources(PonyEngine.Resource.Ext PUBLIC FILE_SET CXX_MODULES FILES 
	"Source/Main.cppm"
	"Source/Main-CollectionResource.cppm"
	"Source/Main-IResourceHub.cppm"
	"Source/Main-IResourceLoader.cppm"
	"Source/Main-IResourceLoadRequest.cppm"
	"Source/Main-IResourceLoadRequestObserver.cppm"
	"Source/Main-IResourceProvider.cppm"
	"Source/Main-ResourceCollection.cppm"
	"Source/Main-ResourceLoadContext.cppm"
	"Source/Main-ResourceLoadData.cppm"
	"Source/Main-ResourceLoadInfo.cppm"
	"Source/Main-ResourceType.cppm"
)

set_target_properties(PonyEngine.Resource.Ext PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.Resource.Ext PUBLIC
	PonyEngine.Core
	PonyEngine.Resource
)
