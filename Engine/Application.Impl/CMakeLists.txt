message(STATUS "Configuring PonyEngine.Application.Impl")

message(VERBOSE "Configuring parameters")
set(PONY_ENGINE_ROOT_PATH "" CACHE STRING "Root path. It must be relative to an executable directory, and the folder must exist at runtime. Empty path is valid.")
option(PONY_ENGINE_CREATE_CONSOLE "Enable console. It's supported on Windows only." OFF)
option(PONY_ENGINE_DEFAULT_LOGGER "Enable default logger. It logs everything to a console." ON)
option(PONY_ENGINE_CONSOLE_LOG "Enable standard c++ console." ON)
option(PONY_ENGINE_PLATFORM_CONSOLE_LOG "Enable platform console." ON)
set(PONY_APP_ICON "" CACHE FILEPATH "Application icon path. Its format depends on a platform. If it's '<Default>', the engine icon is used.")
set(PONY_APP_CURSOR "" CACHE FILEPATH "Application cursor path. Its format depends on a platform.")
set(PONY_ENGINE_PLATFORM_MESSAGE_TICK_ORDER "0" CACHE STRING "PonyEngine application platform message service tick order. It must be an int32 number.")

message(VERBOSE "Configuring target")
if(PONY_WINDOWS)
	add_executable(PonyEngine.Application.Impl WIN32)
else()
	add_executable(PonyEngine.Application.Impl)
endif()

target_sources(PonyEngine.Application.Impl PRIVATE FILE_SET CXX_MODULES FILES
	"Source/Private/Application.Impl.cppm"
	"Source/Private/Application.Impl-App.cppm"
	"Source/Private/Application.Impl-AppDataManager.cppm"
	"Source/Private/Application.Impl-Console.cppm"
	"Source/Private/Application.Impl-DefaultLogger.cppm"
	"Source/Private/Application.Impl-ExitCodes.cppm"
	"Source/Private/Application.Impl-LoggerManager.cppm"
	"Source/Private/Application.Impl-ModuleManager.cppm"
	"Source/Private/Application.Impl-Path.cppm"
	"Source/Private/Application.Impl-PathManager.cppm"
	"Source/Private/Application.Impl-PlatformMessageService.cppm"
	"Source/Private/Application.Impl-Process.cppm"
	"Source/Private/Application.Impl-ServiceManager.cppm"
)

if(PONY_WINDOWS)
	message(VERBOSE "Configuring headers for Windows")
	target_include_directories(PonyEngine.Application.Impl PRIVATE
		"Include/Private/Windows"
	)

	message(VERBOSE "Configuring sources for Windows")
	target_sources(PonyEngine.Application.Impl PRIVATE
		"Source/Main.Windows.cpp"
)

	message(VERBOSE "Configuring data for Windows")
	configure_file("Data/Windows/Application.manifest.in" Application.manifest)
	target_sources(PonyEngine.Application.Impl PRIVATE 
		Application.manifest
		"Data/Windows/Resource.rc"
	)
endif()

message(VERBOSE "Configuring defines")
if(PONY_ENGINE_ROOT_PATH)
	pony_validate_path(PONY_ENGINE_ROOT_PATH false true)
else()
	set(PONY_ENGINE_ROOT_PATH "") # Remove all possible OFF FALSE and things like that.
endif()
if(PONY_APP_ICON STREQUAL "<Default>")
	if(PONY_WINDOWS)
		set(PONY_APP_ICON "${PONY_ROOT}/Logo/Windows/Logo.ico")
	endif()
endif()
pony_validate_tick_order(PONY_ENGINE_PLATFORM_MESSAGE_TICK_ORDER)
target_compile_definitions(PonyEngine.Application.Impl PRIVATE
	PONY_COMPANY_NAME=${PONY_COMPANY_NAME} 
	PONY_PROJECT_NAME=${PONY_PROJECT_NAME} 
	PONY_PROJECT_VERSION=${PONY_PROJECT_VERSION}
	PONY_COMPANY_TITLE=${PONY_COMPANY_TITLE} 
	PONY_PROJECT_TITLE=${PONY_PROJECT_TITLE}
	PONY_ENGINE_ROOT_PATH=${PONY_ENGINE_ROOT_PATH}
	$<$<BOOL:${PONY_ENGINE_CREATE_CONSOLE}>:PONY_ENGINE_CREATE_CONSOLE>
	$<$<BOOL:${PONY_ENGINE_DEFAULT_LOGGER}>:PONY_ENGINE_DEFAULT_LOGGER>
	$<$<BOOL:${PONY_ENGINE_CONSOLE_LOG}>:PONY_ENGINE_CONSOLE_LOG>
	$<$<BOOL:${PONY_ENGINE_PLATFORM_CONSOLE_LOG}>:PONY_ENGINE_PLATFORM_CONSOLE_LOG>
	$<$<BOOL:${PONY_APP_ICON}>:PONY_APP_ICON=${PONY_APP_ICON}>
	$<$<BOOL:${PONY_APP_CURSOR}>:PONY_APP_CURSOR=${PONY_APP_CURSOR}>
	PONY_ENGINE_PLATFORM_MESSAGE_TICK_ORDER=${PONY_ENGINE_PLATFORM_MESSAGE_TICK_ORDER}
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Application.Impl PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
	OUTPUT_NAME "${PONY_PROJECT_NAME}"
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Application.Impl PUBLIC
	PonyEngine.Application.Ext
)
target_link_libraries(PonyEngine.Application.Impl PRIVATE
	PonyEngine.Core
	PonyEngine.Log
)
