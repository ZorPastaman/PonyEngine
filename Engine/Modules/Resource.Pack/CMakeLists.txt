message(STATUS "Configuring PonyEngine.Resource.Pack feature module")

add_library(PonyEngine.Resource.Pack STATIC)

target_sources(PonyEngine.Resource.Pack PUBLIC FILE_SET CXX_MODULES FILES 
	"Source/Pack.cppm"
	"Source/Pack-AccessType.cppm"
	"Source/Pack-Format.cppm"
	"Source/Pack-IPackMountRequest.cppm"
	"Source/Pack-IPackService.cppm"
	"Source/Pack-IPackUnmountRequest.cppm"
	"Source/Pack-PackHandle.cppm"
)

set_target_properties(PonyEngine.Resource.Pack PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.Resource.Pack PUBLIC
	PonyEngine.Core
	PonyEngine.Resource
	PonyEngine.Resource.Ext
)
