message(STATUS "Configuring PonyEngine.File.Impl feature module")

add_library(PonyEngine.File.Impl STATIC)

target_sources(PonyEngine.File.Impl PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/File.cppm"
	"Source/File-FileInfo.cppm"
	"Source/File-ReadRequest.cppm"
	"Source/File-Request.cppm"
	"Source/File-WriteRequest.cppm"
)

set_target_properties(PonyEngine.File.Impl PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.File.Impl PRIVATE
	PonyEngine.Core
	PonyEngine.File
)
