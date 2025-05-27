message(STATUS "Configuring PonyEngine.Platform")
add_library(PonyEngine.Platform STATIC)

message(STATUS "Configuring sources")
target_sources(PonyEngine.Platform PUBLIC FILE_SET CXX_MODULES FILES 
	"Source/Public/Platform/Platform.cppm"
)

if (WIN32)
	message(STATUS "Configuring for Windows")

	message(STATUS "Configuring headers for Windows")
	target_include_directories(PonyEngine.Platform PUBLIC 
		"Include/Public/Windows"
	)
endif()

message(STATUS "Setting build options")
set_build_options(PonyEngine.Platform TRUE)

message(STATUS "Setting globals")
set_property(GLOBAL APPEND PROPERTY PONY_ENGINE_API PonyEngine.Platform)
