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
	add_executable(PonyEngine.Application.Main WIN32)
else()
	add_executable(PonyEngine.Application.Main)
endif()

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Application.Main PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Private/Application.Main/Application.Main.cppm"
	"Source/Private/Application.Main/Application.Main-App.cppm"
	"Source/Private/Application.Main/Application.Main-DefaultLogger.cppm"
	"Source/Private/Application.Main/Application.Main-ExitCodes.cppm"
	"Source/Private/Application.Main/Application.Main-PlatformPaths.cppm"
)

if(PONY_WINCORE)
	message(VERBOSE "Configuring sources for WinCore")
	target_sources(PonyEngine.Application.Main PRIVATE FILE_SET CXX_MODULES FILES 
		"Source/Private/Application.Main/WinCore/Application.Main.WinCore.cppm"
	)
endif()

if(PONY_WINDOWS)
	message(VERBOSE "Configuring sources for Windows")
	target_sources(PonyEngine.Application.Main PRIVATE FILE_SET CXX_MODULES FILES 
		"Source/Private/Application.Main/Windows/Application.Main.Windows.cppm"
		"Source/Private/Application.Main/Windows/Application.Main.Windows-Console.cppm"
		"Source/Private/Application.Main/Windows/Application.Main.Windows-Paths.cppm"
		"Source/Private/Application.Main/Windows/Application.Main.Windows-Process.cppm"
		"Source/Private/Application.Main/Windows/Application.Main.Windows-QuitChecker.cppm"
	)
	 target_sources(PonyEngine.Application.Main PRIVATE
		"Source/Main.Windows.cpp"
	)

	message(VERBOSE "Configuring manifest for Windows")
	configure_file("Data/Windows/Application.manifest.in" Application.manifest)
	target_sources(PonyEngine.Application.Main PRIVATE Application.manifest)
endif()

message(VERBOSE "Configuring defines")
if(PONY_ENGINE_CREATE_CONSOLE)
	target_compile_definitions(PonyEngine.Application.Main PRIVATE PONY_ENGINE_CREATE_CONSOLE)
endif()
target_compile_definitions(PonyEngine.Application.Main PRIVATE PONY_COMPANY_NAME=${PONY_COMPANY_NAME} PONY_PROJECT_NAME=${PONY_PROJECT_NAME})

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Application.Main PROPERTIES 
	CXX_STANDARD 23
	POSITION_INDEPENDENT_CODE TRUE
	OUTPUT_NAME "${PONY_PROJECT_NAME}"
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Application.Main PRIVATE
	PonyEngine.Core
)
