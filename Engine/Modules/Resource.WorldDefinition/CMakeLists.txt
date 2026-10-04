message(STATUS "Configuring PonyEngine.Resource.WorldDefinition feature module")

add_library(PonyEngine.Resource.WorldDefinition STATIC)

target_sources(PonyEngine.Resource.WorldDefinition PRIVATE FILE_SET CXX_MODULES FILES
	"Source/WorldDefinition.cppm"
 )

set_target_properties(PonyEngine.Resource.WorldDefinition PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.Resource.WorldDefinition PRIVATE
	PonyEngine.Core
	PonyEngine.Resource
	PonyEngine.Resource.Ext
	PonyEngine.World
)
