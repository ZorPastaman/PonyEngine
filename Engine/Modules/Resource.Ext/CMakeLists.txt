message(STATUS "Configuring PonyEngine.Resource.Ext feature module")

add_library(PonyEngine.Resource.Ext STATIC)

target_sources(PonyEngine.Resource.Ext PUBLIC FILE_SET CXX_MODULES FILES 
	"Source/Resource.cppm"
	"Source/Resource-CollectionResource.cppm"
	"Source/Resource-IFileDataAccess.cppm"
	"Source/Resource-ILoadableDataAccess.cppm"
	"Source/Resource-ILoadableResource.cppm"
	"Source/Resource-ILoadContext.cppm"
	"Source/Resource-IMemoryDataAccess.cppm"
	"Source/Resource-IResourceHub.cppm"
	"Source/Resource-IResourceLoader.cppm"
	"Source/Resource-IResourceLoadRequest.cppm"
	"Source/Resource-IResourceProvider.cppm"
	"Source/Resource-ResourceCollection.cppm"
	"Source/Resource-ResourceType.cppm"
)

set_target_properties(PonyEngine.Resource.Ext PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.Resource.Ext PUBLIC
	PonyEngine.Core
	PonyEngine.Resource
)
