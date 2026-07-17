message(STATUS "Configuring PonyEngine.Application")

message(VERBOSE "Configuring environment")
include("CMake/Module.cmake")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Application STATIC)

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.Application PUBLIC
	"Include/Public"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Application PUBLIC FILE_SET CXX_MODULES FILES 
	"Source/Main.cppm"
	"Source/Main-FlowState.cppm"
	"Source/Main-IApplication.cppm"
	"Source/Main-IModule.cppm"
	"Source/Main-IModuleContext.cppm"
	"Source/Main-IService.cppm"
	"Source/Main-ITickable.cppm"
	"Source/Main-TempBuffer.cppm"
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Application PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Application PUBLIC
	PonyEngine.Core
	PonyEngine.Log
)
