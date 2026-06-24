message(STATUS "Configuring PonyEngine.File.Impl")

message(VERBOSE "Configuring target")
add_library(PonyEngine.File.Impl STATIC)

target_sources(PonyEngine.File.Impl PRIVATE FILE_SET CXX_MODULES BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}" FILES
	"Source/Main.cppm"
	"Source/Main-FileInfo.cppm"
	"Source/Main-ReadRequest.cppm"
	"Source/Main-Request.cppm"
	"Source/Main-RequestVariant.cppm"
	"Source/Main-WriteRequest.cppm"
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.File.Impl PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
if(NOT TARGET PonyEngine.File)
	message(FATAL_ERROR "PonyEngine.File wasn't configured")
endif()
target_link_libraries(PonyEngine.File.Impl PRIVATE
	PonyEngine.File
	PonyEngine.Core
)
