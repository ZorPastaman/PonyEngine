message(STATUS "Configuring PonyEngine.Application.Main")

message(VERBOSE "Validating settings")
if(PONY_ENGINE_CREATE_CONSOLE)
	if(NOT PONY_WINCORE)
		message(FATAL_ERROR "PONY_ENGINE_CREATE_CONSOLE is set but the current platform doesn't support a console")
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
target_sources(PonyEngine.Application.Main PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Private/Application.Main/Application.Main.cppm"
	"Source/Private/Application.Main/Application.Main-App.cppm"
	"Source/Private/Application.Main/Application.Main-AppDataManager.cppm"
	"Source/Private/Application.Main/Application.Main-Console.cppm"
	"Source/Private/Application.Main/Application.Main-DefaultLogger.cppm"
	"Source/Private/Application.Main/Application.Main-ExitCodes.cppm"
	"Source/Private/Application.Main/Application.Main-FlowManager.cppm"
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

	 target_sources(PonyEngine.Application.Main PRIVATE
		"Source/Main.Windows.cpp"
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
if(PONY_ENGINE_CREATE_CONSOLE)
	target_compile_definitions(PonyEngine.Application.Main PRIVATE PONY_ENGINE_CREATE_CONSOLE)
endif()
if(PONY_CONSOLE_LOG)
	target_compile_definitions(PonyEngine.Application.Main PRIVATE PONY_CONSOLE_LOG)
endif()
if(PONY_PLATFORM_CONSOLE_LOG)
	target_compile_definitions(PonyEngine.Application.Main PRIVATE PONY_PLATFORM_CONSOLE_LOG)
endif()
if(PONY_ENGINE_DEFAULT_LOGGER)
	target_compile_definitions(PonyEngine.Application.Main PRIVATE PONY_ENGINE_DEFAULT_LOGGER)
endif()
if(PONY_APP_ICON)
	target_compile_definitions(PonyEngine.Application.Main PRIVATE PONY_APP_ICON)
endif()
if(PONY_APP_CURSOR)
	target_compile_definitions(PonyEngine.Application.Main PRIVATE PONY_APP_CURSOR)
endif()
if(NOT PONY_ENGINE_ROOT_PATH)
	set(PONY_ENGINE_ROOT_PATH "")
endif()
target_compile_definitions(PonyEngine.Application.Main PRIVATE 
	PONY_COMPANY_NAME=${PONY_COMPANY_NAME} PONY_PROJECT_NAME=${PONY_PROJECT_NAME} PONY_PROJECT_VERSION=${PONY_PROJECT_VERSION}
	PONY_COMPANY_TITLE=${PONY_COMPANY_TITLE} PONY_PROJECT_TITLE=${PONY_PROJECT_TITLE}
	PONY_ENGINE_ROOT_PATH=${PONY_ENGINE_ROOT_PATH}
	PONY_ENGINE_MAIN_DATA_ORDER=${PONY_ENGINE_MAIN_DATA_ORDER}
	PONY_ENGINE_MESSAGE_LOOP_ORDER=${PONY_ENGINE_MESSAGE_LOOP_ORDER} PONY_ENGINE_MESSAGE_LOOP_TICK_ORDER=${PONY_ENGINE_MESSAGE_LOOP_TICK_ORDER}
)

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
