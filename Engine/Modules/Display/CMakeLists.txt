message(STATUS "Configuring PonyEngine.Display feature module")

add_library(PonyEngine.Display STATIC)

target_sources(PonyEngine.Display PUBLIC FILE_SET CXX_MODULES FILES 
	"Source/Display.cppm"
	"Source/Display-DisplayHandle.cppm"
	"Source/Display-DisplayInfo.cppm"
	"Source/Display-IDisplayService.cppm"
)

set_target_properties(PonyEngine.Display PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.Display PUBLIC
	PonyEngine.Core
)
