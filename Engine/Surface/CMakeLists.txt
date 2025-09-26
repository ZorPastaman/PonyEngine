message(STATUS "Configuring PonyEngine.Surface")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Surface STATIC)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Surface PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Public/Surface/Surface.cppm"
	"Source/Public/Surface/Surface-ISurfaceService.cppm"
	"Source/Public/Surface/Surface-SurfacePositionMode.cppm"
	"Source/Public/Surface/Surface-SurfaceStyle.cppm"
	"Source/Public/Surface/Surface-Utility.cppm"
	"Source/Public/Surface/Surface-SurfaceRect.cppm"
)

if(PONY_WINDOWS)
	message(VERBOSE "Configuring sources for Windows")
	target_sources(PonyEngine.Surface PUBLIC FILE_SET CXX_MODULES FILES
		"Source/Public/Surface/Windows/Surface.Windows.cppm"
		"Source/Public/Surface/Windows/Surface.Windows-IMessageObserver.cppm"
		"Source/Public/Surface/Windows/Surface.Windows-IRawInputObserver.cppm"
		"Source/Public/Surface/Windows/Surface.Windows-ISurfaceService.cppm"
		"Source/Public/Surface/Windows/Surface.Windows-Utility.cppm"
	)
endif()

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Surface PROPERTIES 
	CXX_STANDARD 23
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Surface PUBLIC
	PonyEngine.Core
)
