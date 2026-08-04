message(STATUS "Configuring PonyEngine.Surface")

add_library(PonyEngine.Surface STATIC)

target_sources(PonyEngine.Surface PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Main.cppm"
	"Source/Main-ISurfaceObserver.cppm"
	"Source/Main-ISurfaceService.cppm"
	"Source/Main-MathUtility.cppm"
	"Source/Main-RectStyle.cppm"
	"Source/Main-SurfaceFeature.cppm"
)

set_target_properties(PonyEngine.Surface PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.Surface PUBLIC
	PonyEngine.Core
)
