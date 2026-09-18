message(STATUS "Configuring PonyEngine.Log feature module")

include("CMake/Log.cmake")

add_library(PonyEngine.Log STATIC)

target_include_directories(PonyEngine.Log PUBLIC
	"Include/Public"
)

target_sources(PonyEngine.Log PUBLIC FILE_SET CXX_MODULES FILES 
	"Source/Log.cppm"
	"Source/Log-ILogService.cppm"
	"Source/Log-LogHelper.cppm"
	"Source/Log-LogType.cppm"
)

set_target_properties(PonyEngine.Log PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.Log PUBLIC
	PonyEngine.Core
)
