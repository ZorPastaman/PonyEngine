message(STATUS "Configuring PonyEngine.WinInput feature module")

add_library(PonyEngine.WinInput STATIC)

target_sources(PonyEngine.WinInput PUBLIC FILE_SET CXX_MODULES FILES
	"Source/WinInput.cppm"
	"Source/WinInput-IInputDispatcher.cppm"
	"Source/WinInput-IRawInputObserver.cppm"
	"Source/WinInput-Utility.cppm"
)

set_target_properties(PonyEngine.WinInput PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.WinInput PUBLIC
	PonyEngine.Core
)
