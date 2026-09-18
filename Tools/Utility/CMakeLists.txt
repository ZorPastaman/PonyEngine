message(STATUS "Configuring PonyTools.Utility")

add_library(PonyTools.Utility STATIC)

target_sources(PonyTools.Utility PUBLIC FILE_SET CXX_MODULES FILES 
	"Source/DepFile.cppm"
	"Source/DepFile-DepData.cppm"
	"Source/DepFile-DepRule.cppm"
	"Source/FileSystem.cppm"
	"Source/FileSystem-File.cppm"
	"Source/FileSystem-Path.cppm"
	"Source/Serialization.cppm"
)
