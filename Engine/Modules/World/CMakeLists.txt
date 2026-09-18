message(STATUS "Configuring PonyEngine.World feature")

add_library(PonyEngine.World STATIC)

target_sources(PonyEngine.World PUBLIC FILE_SET CXX_MODULES FILES
	"Source/World.cppm"
	"Source/World-Component.cppm"
	"Source/World-Entity.cppm"
	"Source/World-IWorld.cppm"
	"Source/World-IWorldService.cppm"
	"Source/World-ObjectHandle.cppm"
	"Source/World-QueryParams.cppm"
)

set_target_properties(PonyEngine.World PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.World PUBLIC
	PonyEngine.Core
)
