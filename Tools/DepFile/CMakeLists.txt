message(STATUS "Configuring PonyTools.DepFile")

add_library(PonyTools.DepFile STATIC)

target_sources(PonyTools.DepFile PUBLIC FILE_SET CXX_MODULES FILES 
	"Source/DepFile.cppm"
	"Source/DepFile-DepData.cppm"
	"Source/DepFile-DepRule.cppm"
)
