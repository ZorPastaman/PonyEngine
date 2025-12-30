message(STATUS "Configuring PonyEngine.Core for WinCore")

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Core PUBLIC FILE_SET CXX_MODULES BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}" FILES
	"Source/Public/Platform.WinCore.cppm"
	"Source/Public/Platform.WinCore-ComPtr.cppm"
	"Source/Public/Platform.WinCore-GUID.cppm"
)

message(VERBOSE "Configuring defines")
target_compile_definitions(PonyEngine.Core PUBLIC
	PONY_WINCORE
)
