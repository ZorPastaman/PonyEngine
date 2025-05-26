message(STATUS "Configuring application")
if (WIN32)
	add_executable(PonyApplication WIN32)

	target_sources(PonyApplication PRIVATE FILE_SET CXX_MODULES FILES 
		"Source/Main.Windows.cppm")

	configure_file("Data/Windows/Application.manifest.in" Application.manifest)
	target_sources(PonyApplication PRIVATE Application.manifest)
else()
	message(FATAL_ERROR "Unsupported platform!")
endif()

message(STATUS "Setting build options")
set_build_options(PonyApplication TRUE)

message(STATUS "Setting properties")
set_target_properties(PonyApplication PROPERTIES OUTPUT_NAME "${PROJECT_NAME}")
