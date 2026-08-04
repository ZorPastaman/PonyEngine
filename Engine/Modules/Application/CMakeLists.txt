message(STATUS "Configuring PonyEngine.Application")

if(NOT TARGET PonyEngine.Core)
	message(FATAL_ERROR "PonyEngine.Core wasn't configured")
endif()

include("CMake/Module.cmake")

add_library(PonyEngine.Application STATIC)

target_include_directories(PonyEngine.Application PUBLIC
	"Include/Public"
)

target_sources(PonyEngine.Application PUBLIC FILE_SET CXX_MODULES FILES 
	"Source/Main.cppm"
	"Source/Main-IApplication.cppm"
	"Source/Main-IBuffer.cppm"
	"Source/Main-IModule.cppm"
	"Source/Main-IModuleContext.cppm"
	"Source/Main-IThreadControl.cppm"
	"Source/Main-ITickable.cppm"
	"Source/Main-TickOrder.cppm"
)

set_target_properties(PonyEngine.Application PROPERTIES 
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.Application PUBLIC
	PonyEngine.Core
)
