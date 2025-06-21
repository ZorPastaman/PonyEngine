message(STATUS "Configuring PonyEngine.Application")

message(VERBOSE "Validating settings")
if(PONY_ENGINE_CREATE_CONSOLE)
	if(NOT PONY_WINCORE)
		message(FATAL_ERROR "PONY_ENGINE_CREATE_CONSOLE is set but the current platform doesn't support a console")
	endif()
endif()

if(NOT PONY_COMPANY_NAME)
	message(FATAL_ERROR "PONY_COMPANY_NAME isn't set")
endif()
if(NOT PONY_PROJECT_NAME)
	message(FATAL_ERROR "PONY_PROJECT_NAME isn't set")
endif()
if(NOT PONY_PROJECT_VERSION)
	message(FATAL_ERROR "PONY_PROJECT_VERSION isn't set")
endif()

message(VERBOSE "Configuring target")
if(PONY_WINDOWS)
	add_executable(PonyEngine.Application WIN32)
endif()

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Application PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Private/Application/Application.cppm"
	"Source/Private/Application/Application-App.cppm"
	"Source/Private/Application/Application-AppLogger.cppm"
	"Source/Private/Application/Application-DefaultLogger.cppm"
	"Source/Private/Application/Application-ExitCodes.cppm"
	"Source/Private/Application/Application-PlatformPaths.cppm"
)

if(PONY_WINCORE)
	message(VERBOSE "Configuring sources for WinCore")
	target_sources(PonyEngine.Application PRIVATE FILE_SET CXX_MODULES FILES 
		"Source/Private/Application/WinCore/Application.WinCore.cppm"
	)
endif()

if(PONY_WINDOWS)
	message(VERBOSE "Configuring sources for Windows")
	target_sources(PonyEngine.Application PRIVATE FILE_SET CXX_MODULES FILES 
		"Source/Private/Application/Windows/Application.Windows.cppm"
		"Source/Private/Application/Windows/Application.Windows-Console.cppm"
		"Source/Private/Application/Windows/Application.Windows-Paths.cppm"
		"Source/Private/Application/Windows/Application.Windows-Process.cppm"
		"Source/Private/Application/Windows/Application.Windows-QuitChecker.cppm"
	)
	 target_sources(PonyEngine.Application PRIVATE
		"Source/Main.Windows.cpp"
	)

	message(VERBOSE "Configuring manifest for Windows")
	configure_file("Data/Windows/Application.manifest.in" Application.manifest)
	target_sources(PonyEngine.Application PRIVATE Application.manifest)
endif()

message(VERBOSE "Configuring defines")
if(PONY_ENGINE_CREATE_CONSOLE)
	target_compile_definitions(PonyEngine.Application PRIVATE PONY_ENGINE_CREATE_CONSOLE)
endif()
target_compile_definitions(PonyEngine.Application PRIVATE PONY_COMPANY_NAME=${PONY_COMPANY_NAME} PONY_PROJECT_NAME=${PONY_PROJECT_NAME})

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Application PROPERTIES CXX_STANDARD 23)
set_target_properties(PonyEngine.Application PROPERTIES OUTPUT_NAME "${PONY_PROJECT_NAME}")

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Application PRIVATE
	PonyEngine.Core
)
