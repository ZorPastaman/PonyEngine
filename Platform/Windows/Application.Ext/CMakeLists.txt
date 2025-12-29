message(STATUS "Configuring PonyEngine.Application.Ext for Windows")

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Application.Ext PUBLIC FILE_SET CXX_MODULES BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}" FILES
	"Source/Public/Application.Ext.Windows.cppm"
	"Source/Public/Application.Ext.Windows-IApplicationContext.cppm"
)
