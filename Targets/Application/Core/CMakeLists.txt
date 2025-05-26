message(STATUS "Configuring PonyApplication.Core")
if (WIN32)
	add_executable(PonyApplication.Core WIN32)

	message(STATUS "Configuring sources")
	target_sources(PonyApplication.Core PRIVATE FILE_SET CXX_MODULES FILES 
		"Source/Main.Windows.cppm")

	message(STATUS "Configuring data")
	configure_file("Data/Windows/Application.manifest.in" Application.manifest)
	target_sources(PonyApplication.Core PRIVATE Application.manifest)
else()
	message(FATAL_ERROR "Unsupported platform!")
endif()

message(STATUS "Setting build options")
set_build_options(PonyApplication.Core TRUE)

message(STATUS "Setting properties")
set_target_properties(PonyApplication.Core PROPERTIES OUTPUT_NAME "${PROJECT_NAME}")
