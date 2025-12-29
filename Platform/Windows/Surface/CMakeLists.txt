message(STATUS "Configuring PonyEngine.Surface for Windows")

message(VERBOSE "Configuring sources for Windows")
target_sources(PonyEngine.Surface PUBLIC FILE_SET CXX_MODULES BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}" FILES
	"Source/Public/Surface.Windows.cppm"
	"Source/Public/Surface.Windows-IRawInputObserver.cppm"
	"Source/Public/Surface.Windows-ISurfaceService.cppm"
)
