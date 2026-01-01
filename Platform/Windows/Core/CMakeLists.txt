message(STATUS "Configuring PonyEngine.Core for Windows")

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.Core PUBLIC 
	"Include/Public"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Core PUBLIC FILE_SET CXX_MODULES BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}" FILES
	"Source/Public/Platform.Windows.cppm"
	"Source/Public/Platform.Windows-ComPtr.cppm"
	"Source/Public/Platform.Windows-Cursor.cppm"
	"Source/Public/Platform.Windows-Device.cppm"
	"Source/Public/Platform.Windows-File.cppm"
	"Source/Public/Platform.Windows-GUID.cppm"
	"Source/Public/Platform.Windows-Text.cppm"
)

message(VERBOSE "Configuring defines")
target_compile_definitions(PonyEngine.Core PUBLIC
	PONY_WINDOWS
)
