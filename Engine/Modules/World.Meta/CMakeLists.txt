message(STATUS "Configuring PonyEngine.World.Meta feature module")

add_library(PonyEngine.World.Meta STATIC)

target_sources(PonyEngine.World.Meta PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Meta.cppm"
	"Source/Meta-Description.cppm"
	"Source/Meta-Name.cppm"
)

set_target_properties(PonyEngine.World.Meta PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.World.Meta PUBLIC
	PonyEngine.Core
	PonyEngine.World
)
