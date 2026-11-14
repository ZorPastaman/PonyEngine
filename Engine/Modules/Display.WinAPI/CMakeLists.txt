message(STATUS "Configuring PonyEngine.Display.WinAPI modification module")

target_sources(PonyEngine.Display PUBLIC FILE_SET CXX_MODULES BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}" FILES
	"Source/Display-WindowHandle.cppm"
)
