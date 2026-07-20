message(STATUS "Configuring PonyEngine.Application for Windows")

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Application PUBLIC FILE_SET CXX_MODULES BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}" FILES
	"Source/Main.cppm"
	"Source/Main-IMainData.cppm"
	"Source/Main-IMessagePump.cppm"
	"Source/Main-IResourceProvider.cppm"
)
