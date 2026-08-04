message(STATUS "Configuring PonyEngine.Resource")

add_library(PonyEngine.Resource STATIC)

target_sources(PonyEngine.Resource PUBLIC FILE_SET CXX_MODULES FILES 
	"Source/Main.cppm"
	"Source/Main-IFileResource.cppm"
	"Source/Main-ILoadableResource.cppm"
	"Source/Main-ILoadRequest.cppm"
	"Source/Main-IMemoryResource.cppm"
	"Source/Main-IResource.cppm"
	"Source/Main-IResourceService.cppm"
	"Source/Main-LoadParams.cppm"
	"Source/Main-RequestStatus.cppm"
	"Source/Main-ResourceAvailability.cppm"
	"Source/Main-ResourceID.cppm"
	"Source/Main-ResourceType.cppm"
)

set_target_properties(PonyEngine.Resource PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.Resource PUBLIC
	PonyEngine.Core
)
