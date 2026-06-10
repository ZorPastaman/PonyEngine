message(STATUS "Configuring PonyEngine.File")

message(VERBOSE "Configuring target")
add_library(PonyEngine.File STATIC)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.File PUBLIC FILE_SET CXX_MODULES FILES 
	"Source/Main.cppm"
	"Source/Main-FileAccess.cppm"
	"Source/Main-FileFlag.cppm"
	"Source/Main-FileOpenMode.cppm"
	"Source/Main-FileParams.cppm"
	"Source/Main-IFile.cppm"
	"Source/Main-IFileService.cppm"
	"Source/Main-IReadRequest.cppm"
	"Source/Main-IRequest.cppm"
	"Source/Main-IWriteRequest.cppm"
	"Source/Main-ReadParams.cppm"
	"Source/Main-RequestStatus.cppm"
	"Source/Main-WriteParams.cppm"
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.File PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.File PUBLIC
	PonyEngine.Core
)
