message(STATUS "Configuring PonyEngine.Resource.World.Ext feature module")

add_library(PonyEngine.Resource.World.Ext STATIC)

target_sources(PonyEngine.Resource.World.Ext PUBLIC FILE_SET CXX_MODULES FILES
	"Source/World.cppm"
	"Source/World-IComponentDeserializer.cppm"
	"Source/World-IObjectDeserializer.cppm"
	"Source/World-IWorldDefinitionLoader.cppm"
	"Source/World-IWorldDeserializationRequest.cppm"
)

set_target_properties(PonyEngine.Resource.World.Ext PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.Resource.World.Ext PUBLIC
	PonyEngine.Core
	PonyEngine.Resource
	PonyEngine.Resource.Ext
	PonyEngine.World
)
