message(STATUS "Configuring PonyEngine.Resource.Pack")

if(NOT TARGET PonyEngine.Core)
	message(FATAL_ERROR "PonyEngine.Core wasn't configured")
endif()
if(NOT TARGET PonyEngine.Resource)
	message(FATAL_ERROR "PonyEngine.Resource wasn't configured")
endif()
if(NOT TARGET PonyEngine.Resource.Ext)
	message(FATAL_ERROR "PonyEngine.Resource.Ext wasn't configured")
endif()

add_library(PonyEngine.Resource.Pack STATIC)

target_sources(PonyEngine.Resource.Pack PUBLIC FILE_SET CXX_MODULES FILES 
	"Source/Main.cppm"
	"Source/Main-AccessType.cppm"
	"Source/Main-IPackMountRequest.cppm"
	"Source/Main-IPackService.cppm"
	"Source/Main-IPackUnmountRequest.cppm"
	"Source/Main-PackHandle.cppm"
	"Source/Main-PackMountRequestStatus.cppm"
	"Source/Main-ResourceInfo.cppm"
)

set_target_properties(PonyEngine.Resource.Pack PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.Resource.Pack PUBLIC
	PonyEngine.Core
	PonyEngine.Resource
	PonyEngine.Resource.Ext
)
