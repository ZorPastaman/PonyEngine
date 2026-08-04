message(STATUS "Configuring PonyEngine.Log")

if(NOT TARGET PonyEngine.Core)
	message(FATAL_ERROR "PonyEngine.Core wasn't configured")
endif()

include("CMake/Log.cmake")

add_library(PonyEngine.Log STATIC)

target_include_directories(PonyEngine.Log PUBLIC
	"Include/Public"
)

target_sources(PonyEngine.Log PUBLIC FILE_SET CXX_MODULES FILES 
	"Source/Main.cppm"
	"Source/Main-ILogService.cppm"
	"Source/Main-LogHelper.cppm"
	"Source/Main-LogType.cppm"
)

set_target_properties(PonyEngine.Log PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.Log PUBLIC
	PonyEngine.Core
)
