message(STATUS "Configuring PonyEngine.Resource.World feature module")

add_library(PonyEngine.Resource.World STATIC)

target_sources(PonyEngine.Resource.World PUBLIC FILE_SET CXX_MODULES FILES
	"Source/World.cppm"
	"Source/World-CopyComponentDeserializer.cppm"
	"Source/World-IComponentDeserializer.cppm"
	"Source/World-IObjectDeserializer.cppm"
	"Source/World-IWorldDefinitionLoader.cppm"
	"Source/World-IWorldDeserializationRequest.cppm"
)

set_target_properties(PonyEngine.Resource.World PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.Resource.World PUBLIC
	PonyEngine.Core
	PonyEngine.Resource
	PonyEngine.Resource.Ext
	PonyEngine.World
)
