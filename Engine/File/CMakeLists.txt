message(STATUS "Configuring PonyEngine.File")

message(VERBOSE "Configuring target")
add_library(PonyEngine.File STATIC)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.File PUBLIC FILE_SET CXX_MODULES FILES
	"Source/Public/File.cppm"
	"Source/Public/File-IFileService.cppm"
	"Source/Public/File-IReadStream.cppm"
	"Source/Public/File-IWriteStream.cppm"
	"Source/Public/File-ReadMode.cppm"
	"Source/Public/File-WriteMode.cppm"
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.File PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.File PRIVATE
	PonyEngine.Core
)
