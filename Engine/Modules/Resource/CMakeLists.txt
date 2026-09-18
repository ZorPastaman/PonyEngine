message(STATUS "Configuring PonyEngine.Resource feature module")

add_library(PonyEngine.Resource STATIC)

target_sources(PonyEngine.Resource PUBLIC FILE_SET CXX_MODULES FILES 
	"Source/Resource.cppm"
	"Source/Resource-IResourceRequest.cppm"
	"Source/Resource-IResourceService.cppm"
	"Source/Resource-ResourceID.cppm"
)

set_target_properties(PonyEngine.Resource PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.Resource PUBLIC
	PonyEngine.Core
)
