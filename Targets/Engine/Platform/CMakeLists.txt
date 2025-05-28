message(STATUS "Configuring PonyEngine.Platform")
add_library(PonyEngine.Platform STATIC)

message(STATUS "Configuring sources")
target_sources(PonyEngine.Platform PUBLIC FILE_SET CXX_MODULES FILES 
	"Source/Public/Platform/Platform.cppm"
)

set (PONY_IS_WINCORE FALSE)

if(WIN32)
	message(STATUS "Configuring for Windows")
	message(STATUS "Configuring headers for Windows")
	target_include_directories(PonyEngine.Platform PUBLIC 
		"Include/Public/Windows"
	)

	message(STATUS "Configuring sources for Windows")
	target_sources(PonyEngine.Platform PUBLIC FILE_SET CXX_MODULES FILES
		"Source/Public/Platform/Windows/Platform.Windows.cppm"
		"Source/Public/Platform/Windows/Platform.Windows-Cursor.cppm"
		"Source/Public/Platform/Windows/Platform.Windows-Module.cppm"
	)

	set(PONY_IS_WINCORE TRUE)
endif()

if(PONY_IS_WINCORE)
	message(STATUS "Configuring for WinCore")
	message(STATUS "Configuring headers for WinCore")
	target_include_directories(PonyEngine.Platform PUBLIC 
		"Include/Public/WinCore"
	)

	message(STATUS "Configuring sources for WinCore")
	target_sources(PonyEngine.Platform PUBLIC FILE_SET CXX_MODULES FILES
		"Source/Public/Platform/WinCore/Platform.WinCore.cppm"
		"Source/Public/Platform/WinCore/Platform.WinCore-GUID.cppm"
		"Source/Public/Platform/WinCore/Platform.WinCore-Utility.cppm"
	)
endif()

message(STATUS "Configuring dependencies")
target_link_libraries(PonyEngine.Platform PRIVATE
	PonyEngine.Utility
)

message(STATUS "Setting build options")
set_build_options(PonyEngine.Platform TRUE)

message(STATUS "Setting globals")
set_property(GLOBAL APPEND PROPERTY PONY_API PonyEngine.Platform)
