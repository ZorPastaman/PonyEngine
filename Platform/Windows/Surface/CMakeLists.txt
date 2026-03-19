message(STATUS "Configuring PonyEngine.Surface for Windows")

message(VERBOSE "Configuring sources for Windows")
target_sources(PonyEngine.Surface PUBLIC FILE_SET CXX_MODULES BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}" FILES
	"Source/Public/Main.cppm"
	"Source/Public/Main-IRawInputObserver.cppm"
	"Source/Public/Main-ISurfaceService.cppm"
)
