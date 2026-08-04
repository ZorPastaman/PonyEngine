message(STATUS "Configuring PonyEngine.Core for Windows")

target_include_directories(PonyEngine.Core PUBLIC 
	"Include/Public"
)

target_sources(PonyEngine.Core PUBLIC FILE_SET CXX_MODULES BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}" FILES
	"Source/Platform.Windows.cppm"
	"Source/Platform.Windows-ComPtr.cppm"
	"Source/Platform.Windows-Device.cppm"
	"Source/Platform.Windows-File.cppm"
	"Source/Platform.Windows-GUID.cppm"
	"Source/Platform.Windows-Text.cppm"
)

target_compile_definitions(PonyEngine.Core PUBLIC
	PONY_WINDOWS
)
