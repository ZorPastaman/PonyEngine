message(STATUS "Configuring PonyEngine.World")

if(NOT TARGET PonyEngine.Core)
	message(FATAL_ERROR "PonyEngine.Core wasn't configured")
endif()

add_library(PonyEngine.World STATIC)

target_sources(PonyEngine.World PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Main.cppm"
	"Source/Main-Component.cppm"
	"Source/Main-Entity.cppm"
	"Source/Main-IWorld.cppm"
	"Source/Main-IWorldService.cppm"
	"Source/Main-ObjectHandle.cppm"
	"Source/Main-QueryParams.cppm"
)

set_target_properties(PonyEngine.World PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.World PUBLIC
	PonyEngine.Core
)
