message(STATUS "Configuring PonyEngine.Application")
if (PONY_WINDOWS)
	add_executable(PonyEngine.Application WIN32)

	message(STATUS "Configuring sources for Windows")
	target_sources(PonyEngine.Application PRIVATE FILE_SET CXX_MODULES FILES 
		"Source/Main.Windows.cppm"
		"Source/Private/Application/Windows/Application.Windows.cppm"
		"Source/Private/Application/Windows/Application.Windows-Console.cppm"
		"Source/Private/Application/Windows/Application.Windows-Process.cppm"
	 )

	message(STATUS "Configuring data for Windows")
	configure_file("Data/Windows/Application.manifest.in" Application.manifest)
	target_sources(PonyEngine.Application PRIVATE Application.manifest)
else()
	message(FATAL_ERROR "Unsupported platform!")
endif()

message(STATUS "Configuring sources")
target_sources(PonyEngine.Application PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Private/Application/Application.cppm"
	"Source/Private/Application/Application-ExitCodes.cppm"
)

message(STATUS "Configuring dependencies")
target_link_libraries(PonyEngine.Application PRIVATE
	PonyEngine.Core
)
get_property(PONY_APP_MODULES_VALUE GLOBAL PROPERTY PONY_APP_MODULES)
message(STATUS "Application module list: ${PONY_APP_MODULES_VALUE}")
target_link_libraries(PonyEngine.Application PRIVATE ${PONY_APP_MODULES_VALUE})

message(STATUS "Setting build options")
set_build_options(PonyEngine.Application TRUE)

message(STATUS "Setting properties")
set_target_properties(PonyEngine.Application PROPERTIES OUTPUT_NAME "${PROJECT_NAME}")

message(STATUS "Setting globals")
set_property(GLOBAL APPEND PROPERTY PONY_INSTALL PonyEngine.Application)
