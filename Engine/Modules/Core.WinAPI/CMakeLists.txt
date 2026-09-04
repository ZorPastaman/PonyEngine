message(STATUS "Configuring PonyEngine.Core.WinAPI modification module")

target_sources(PonyEngine.Core PUBLIC FILE_SET CXX_MODULES BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}" FILES
	"Source/FileSystem.cppm"
	"Source/FileSystem-Module.cppm"
	"Source/FileSystem-Path.cppm"
	"Source/Format.cppm"
	"Source/Format-GUID.cppm"
	"Source/Memory.cppm"
	"Source/Memory-ComPtr.cppm"
	"Source/Text.cppm"
	"Source/Text-Conversion.cppm"
)
