message(STATUS "Configuring PonyEngine.World.Hierarchy feature module")

add_library(PonyEngine.World.Hierarchy STATIC)

target_sources(PonyEngine.World.Hierarchy PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Hierarchy.cppm"
	"Source/Hierarchy-Children.cppm"
	"Source/Hierarchy-IHierarchyService.cppm"
	"Source/Hierarchy-LocalTransform.cppm"
	"Source/Hierarchy-Parent.cppm"
	"Source/Hierarchy-Types.cppm"
	"Source/Hierarchy-WorldTransform.cppm"
)

set_target_properties(PonyEngine.World.Hierarchy PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.World.Hierarchy PUBLIC
	PonyEngine.Core
	PonyEngine.World
)
