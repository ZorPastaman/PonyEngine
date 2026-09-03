message(STATUS "Configuring PonyEngine.File")

add_library(PonyEngine.File STATIC)

target_sources(PonyEngine.File PUBLIC FILE_SET CXX_MODULES FILES 
	"Source/File.cppm"
	"Source/File-FileAccess.cppm"
	"Source/File-FileFlag.cppm"
	"Source/File-FileOpenMode.cppm"
	"Source/File-FileParams.cppm"
	"Source/File-IFile.cppm"
	"Source/File-IFileService.cppm"
	"Source/File-IReadRequest.cppm"
	"Source/File-IRequest.cppm"
	"Source/File-IWriteRequest.cppm"
	"Source/File-ReadParams.cppm"
	"Source/File-WriteParams.cppm"
)

set_target_properties(PonyEngine.File PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.File PUBLIC
	PonyEngine.Core
)
