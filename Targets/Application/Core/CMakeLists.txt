message(STATUS "Configuring PonyApplication.Core")
if (WIN32)
	message(STATUS "Configuring for Windows")
	add_executable(PonyApplication.Core WIN32)

	message(STATUS "Configuring sources for Windows")
	target_sources(PonyApplication.Core PRIVATE FILE_SET CXX_MODULES FILES 
		"Source/Main.Windows.cppm"
	)

	message(STATUS "Configuring data for Windows")
	configure_file("Data/Windows/Application.manifest.in" Application.manifest)
	target_sources(PonyApplication.Core PRIVATE Application.manifest)
else()
	message(FATAL_ERROR "Unsupported platform!")
endif()

message(STATUS "Configuring dependencies")
target_link_libraries(PonyApplication.Core PRIVATE PonyEngine.Platform)

message(STATUS "Setting build options")
set_build_options(PonyApplication.Core TRUE)

message(STATUS "Setting properties")
set_target_properties(PonyApplication.Core PROPERTIES OUTPUT_NAME "${PROJECT_NAME}")

message(STATUS "Setting globals")
set_property(GLOBAL APPEND PROPERTY PONY_ENGINE_INSTALL PonyApplication.Core)
