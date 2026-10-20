message(STATUS "Configuring PonyTools.Utility")

add_library(PonyTools.Utility STATIC)

target_sources(PonyTools.Utility PUBLIC FILE_SET CXX_MODULES FILES 
	"Source/DepFile.cppm"
	"Source/DepFile-DepData.cppm"
	"Source/DepFile-DepRule.cppm"
	"Source/FileSystem.cppm"
	"Source/FileSystem-File.cppm"
	"Source/FileSystem-Path.cppm"
	"Source/Memory.cppm"
	"Source/Memory-ByteWriter.cppm"
	"Source/Memory-Utility.cppm"
	"Source/Serialization.cppm"
)

target_link_libraries(PonyTools.Utility PRIVATE
	PonyEngine.Core
)
