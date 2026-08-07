message(STATUS "Configuring PonyEngine.File")

if(NOT TARGET PonyEngine.Core)
	message(FATAL_ERROR "PonyEngine.Core wasn't configured")
endif()

add_library(PonyEngine.File STATIC)

target_sources(PonyEngine.File PUBLIC FILE_SET CXX_MODULES FILES 
	"Source/Main.cppm"
	"Source/Main-FileAccess.cppm"
	"Source/Main-FileFlag.cppm"
	"Source/Main-FileOpenMode.cppm"
	"Source/Main-FileParams.cppm"
	"Source/Main-IFile.cppm"
	"Source/Main-IFileService.cppm"
	"Source/Main-IReadHandler.cppm"
	"Source/Main-IReadRequest.cppm"
	"Source/Main-IRequest.cppm"
	"Source/Main-IWriteHandler.cppm"
	"Source/Main-IWriteRequest.cppm"
	"Source/Main-ReadParams.cppm"
	"Source/Main-RequestStatus.cppm"
	"Source/Main-WriteParams.cppm"
)

set_target_properties(PonyEngine.File PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.File PUBLIC
	PonyEngine.Core
)
