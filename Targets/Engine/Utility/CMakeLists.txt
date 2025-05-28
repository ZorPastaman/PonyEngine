message(STATUS "Configuring PonyEngine.Utility")
add_library(PonyEngine.Utility STATIC)

message(STATUS "Configuring headers")
target_include_directories(PonyEngine.Utility PUBLIC
	"Include/Public"
)

message(STATUS "Configuring sources")
target_sources(PonyEngine.Utility PUBLIC FILE_SET CXX_MODULES FILES 
	"Source/Public/Utility/Utility.cppm"
	"Source/Public/Utility/Utility-SafeFormat.cppm"
)

message(STATUS "Setting build options")
set_build_options(PonyEngine.Utility TRUE)

message(STATUS "Setting globals")
set_property(GLOBAL APPEND PROPERTY PONY_API PonyEngine.Utility)
