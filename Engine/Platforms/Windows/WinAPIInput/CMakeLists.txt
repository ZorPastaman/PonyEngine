message(STATUS "Configuring PonyEngine.WinAPIInput for Windows")

if(NOT TARGET PonyEngine.Core)
	message(FATAL_ERROR "PonyEngine.Core wasn't configured")
endif()

target_sources(PonyEngine.WinAPIInput PUBLIC FILE_SET CXX_MODULES BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}" FILES
	"Source/Main.cppm"
	"Source/Main-IInputDispatcher.cppm"
	"Source/Main-IRawInputObserver.cppm"
)

target_link_libraries(PonyEngine.WinAPIInput PUBLIC
	PonyEngine.Core
)
