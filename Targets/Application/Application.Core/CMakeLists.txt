message(STATUS "Configuring application")
if (WIN32)
	add_executable(Application WIN32 "Main.Windows.cppm")

	target_sources(Application PRIVATE
		FILE_SET CXX_MODULES
		FILES Main.Windows.cppm
	)
else()
	message(FATAL_ERROR "Unsupported platform!")
endif()

message(STATUS "Setting compile options")
set_compile_options(Application TRUE)

message(STATUS "Setting properties")
set_target_properties(Application PROPERTIES OUTPUT_NAME "${PROJECT_NAME}")

message(STATUS "Installing")
install(TARGETS Application RUNTIME DESTINATION .)
