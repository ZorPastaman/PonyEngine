message(STATUS "Configuring PonyEngine.Application")
if(PONY_WINDOWS)
	add_executable(PonyEngine.Application WIN32)
else()
	message(FATAL_ERROR "Unsupported platform!")
endif()

message(STATUS "Configuring sources")
target_sources(PonyEngine.Application PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Private/Application/Application.cppm"
	"Source/Private/Application/Application-App.cppm"
	"Source/Private/Application/Application-AppLogger.cppm"
	"Source/Private/Application/Application-DefaultLogger.cppm"
	"Source/Private/Application/Application-ExitCodes.cppm"
)

if(PONY_WINCORE)
	message(STATUS "Configuring sources for WinCore")
	target_sources(PonyEngine.Application PRIVATE FILE_SET CXX_MODULES FILES 
		"Source/Private/Application/WinCore/Application.WinCore.cppm"
	)
endif()

if(PONY_WINDOWS)
	message(STATUS "Configuring sources for Windows")
	target_sources(PonyEngine.Application PRIVATE FILE_SET CXX_MODULES FILES 
		"Source/Private/Application/Windows/Application.Windows.cppm"
		"Source/Private/Application/Windows/Application.Windows-Console.cppm"
		"Source/Private/Application/Windows/Application.Windows-Process.cppm"
	 )
	 target_sources(PonyEngine.Application PRIVATE
		"Source/Main.Windows.cpp"
	 )

	message(STATUS "Configuring data for Windows")
	configure_file("Data/Windows/Application.manifest.in" Application.manifest)
	target_sources(PonyEngine.Application PRIVATE Application.manifest)
endif()

message(STATUS "Configuring defines")
if(PONY_CREATE_CONSOLE)
	target_compile_definitions(PonyEngine.Application PRIVATE PONY_CREATE_CONSOLE)
endif()
pony_set_log_mask(PonyEngine.Application TRUE)

message(STATUS "Setting properties")
set_target_properties(PonyEngine.Application PROPERTIES OUTPUT_NAME "${PROJECT_NAME}")

message(STATUS "Setting build options")
pony_set_build_options(PonyEngine.Application TRUE)

message(STATUS "Configuring dependencies")
target_link_libraries(PonyEngine.Application PRIVATE
	PonyEngine.Core
)
pony_link_app_modules(PonyEngine.Application)

message(STATUS "Installing")
get_property(PONY_APP_INSTALL_PATH_VALUE GLOBAL PROPERTY PONY_APP_INSTALL_PATH)
message(STATUS "Application destination: ${PONY_APP_INSTALL_PATH_VALUE}")
install(TARGETS PonyEngine.Application RUNTIME DESTINATION ${PONY_APP_INSTALL_PATH_VALUE})
