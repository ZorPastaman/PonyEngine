message(STATUS "Configuring PonyEngine.Application.Main")

message(VERBOSE "Validating settings")
if(PONY_ENGINE_CREATE_CONSOLE)
	if(NOT PONY_WINCORE)
		message(WARNING "PONY_ENGINE_CREATE_CONSOLE is set but the current platform doesn't support a console")
	endif()
endif()

message(VERBOSE "Configuring target")
if(PONY_WINDOWS)
	add_executable(PonyEngine.Application.Main WIN32)
else()
	add_executable(PonyEngine.Application.Main)
endif()

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.Application.Main PRIVATE
	"Include/Private/Common"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Application.Main PRIVATE
	"Source/Main.cpp"
)

target_sources(PonyEngine.Application.Main PRIVATE FILE_SET CXX_MODULES FILES
	"Source/Private/Application.Main/Application.Main.cppm"
	"Source/Private/Application.Main/Application.Main-App.cppm"
	"Source/Private/Application.Main/Application.Main-AppDataManager.cppm"
	"Source/Private/Application.Main/Application.Main-Console.cppm"
	"Source/Private/Application.Main/Application.Main-DefaultLogger.cppm"
	"Source/Private/Application.Main/Application.Main-ExitCodes.cppm"
	"Source/Private/Application.Main/Application.Main-LoggerManager.cppm"
	"Source/Private/Application.Main/Application.Main-MessageLoopManager.cppm"
	"Source/Private/Application.Main/Application.Main-ModuleManager.cppm"
	"Source/Private/Application.Main/Application.Main-Path.cppm"
	"Source/Private/Application.Main/Application.Main-PathManager.cppm"
	"Source/Private/Application.Main/Application.Main-Process.cppm"
	"Source/Private/Application.Main/Application.Main-ServiceManager.cppm"
)

if(PONY_WINDOWS)
	message(VERBOSE "Configuring headers for Windows")
	target_include_directories(PonyEngine.Application.Main PRIVATE
		"Include/Private/Windows"
	)

	message(VERBOSE "Configuring data for Windows")
	configure_file("Data/Windows/Application.manifest.in" Application.manifest)
	configure_file("Data/Windows/Resource.rc.in" Resource.rc)
	target_sources(PonyEngine.Application.Main PRIVATE 
		Application.manifest
		Resource.rc
	)
endif()

message(VERBOSE "Configuring defines")
if(NOT PONY_ENGINE_ROOT_PATH)
	set(PONY_ENGINE_ROOT_PATH "")
endif()
target_compile_definitions(PonyEngine.Application.Main PRIVATE
	PONY_COMPANY_NAME=${PONY_COMPANY_NAME} PONY_PROJECT_NAME=${PONY_PROJECT_NAME} PONY_PROJECT_VERSION=${PONY_PROJECT_VERSION}
	PONY_COMPANY_TITLE=${PONY_COMPANY_TITLE} PONY_PROJECT_TITLE=${PONY_PROJECT_TITLE}
	PONY_ENGINE_ROOT_PATH=${PONY_ENGINE_ROOT_PATH}
	$<$<BOOL:${PONY_ENGINE_CREATE_CONSOLE}>:PONY_ENGINE_CREATE_CONSOLE>
	$<$<BOOL:${PONY_ENGINE_DEFAULT_LOGGER}>:PONY_ENGINE_DEFAULT_LOGGER>
	$<$<BOOL:${PONY_CONSOLE_LOG}>:PONY_CONSOLE_LOG>
	$<$<BOOL:${PONY_PLATFORM_CONSOLE_LOG}>:PONY_PLATFORM_CONSOLE_LOG>
	$<$<BOOL:${PONY_APP_ICON}>:PONY_APP_ICON>
	$<$<BOOL:${PONY_APP_CURSOR}>:PONY_APP_CURSOR>
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Application.Main PROPERTIES 
	CXX_STANDARD 23
	POSITION_INDEPENDENT_CODE TRUE
	OUTPUT_NAME "${PONY_PROJECT_NAME}"
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Application.Main PUBLIC
	PonyEngine.Application.Extension
	PonyEngine.Core
	PonyEngine.Log
)
