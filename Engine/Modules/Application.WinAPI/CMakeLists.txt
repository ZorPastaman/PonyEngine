message(STATUS "Configuring PonyEngine.Application.WinAPI modification module")

target_sources(PonyEngine.Application PUBLIC FILE_SET CXX_MODULES BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}" FILES
	"Source/Application.cppm"
	"Source/Application-IMainData.cppm"
	"Source/Application-IMessagePump.cppm"
)
