message(STATUS "Configuring PonyEngine.Resource")

if(NOT TARGET PonyEngine.Core)
	message(FATAL_ERROR "PonyEngine.Core wasn't configured")
endif()

add_library(PonyEngine.Resource STATIC)

target_sources(PonyEngine.Resource PUBLIC FILE_SET CXX_MODULES FILES 
	"Source/Main.cppm"
	"Source/Main-IResourceRequest.cppm"
	"Source/Main-IResourceRequestObserver.cppm"
	"Source/Main-IResourceService.cppm"
	"Source/Main-RequestStatus.cppm"
	"Source/Main-ResourceID.cppm"
)

set_target_properties(PonyEngine.Resource PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.Resource PUBLIC
	PonyEngine.Core
)
