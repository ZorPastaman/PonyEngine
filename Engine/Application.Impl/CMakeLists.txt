message(STATUS "Configuring PonyEngine.Application.Impl")

message(VERBOSE "Configuring parameters")
set(PONY_ENGINE_ROOT_PATH "" CACHE STRING "Root path. It must be relative to an executable directory, and the folder must exist at runtime. Empty path is valid.")
option(PONY_ENGINE_CREATE_CONSOLE "Enable console. It's supported on Windows only." OFF)
option(PONY_ENGINE_DEFAULT_LOGGER "Enable default logger. It logs everything to a console." ON)
option(PONY_ENGINE_CONSOLE_LOG "Enable standard c++ console." ON)
option(PONY_ENGINE_PLATFORM_CONSOLE_LOG "Enable platform console." ON)
set(PONY_APP_ICON "" CACHE FILEPATH "Application icon path. Its format depends on a platform. If it's '<Default>', the engine icon is used.")
set(PONY_APP_CURSOR "" CACHE FILEPATH "Application cursor path. Its format depends on a platform.")

message(VERBOSE "Configuring target")
if(PONY_WINDOWS)
	add_executable(PonyEngine.Application.Impl WIN32)
else()
	add_executable(PonyEngine.Application.Impl)
endif()

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Application.Impl PRIVATE FILE_SET CXX_MODULES FILES
	"Source/Private/Application.Impl.cppm"
	"Source/Private/Application.Impl-Console.cppm"
	"Source/Private/Application.Impl-DefaultLogger.cppm"
	"Source/Private/Application.Impl-ExitCodes.cppm"
	"Source/Private/Application.Impl-FlowManager.cppm"
	"Source/Private/Application.Impl-InterfaceContainer.cppm"
	"Source/Private/Application.Impl-LoggerManager.cppm"
	"Source/Private/Application.Impl-ModuleDataContainer.cppm"
	"Source/Private/Application.Impl-ModuleManager.cppm"
	"Source/Private/Application.Impl-Name.cppm"
	"Source/Private/Application.Impl-Path.cppm"
	"Source/Private/Application.Impl-ServiceContainer.cppm"
	"Source/Private/Application.Impl-ServiceManager.cppm"
	"Source/Private/Application.Impl-TickableServiceInfo.cppm"
)

if(PONY_WINDOWS)
	message(VERBOSE "Configuring headers for Windows")
	target_include_directories(PonyEngine.Application.Impl PRIVATE
		"Include/Private/Windows"
	)

	target_sources(PonyEngine.Application.Impl PRIVATE FILE_SET CXX_MODULES FILES
		"Source/Private/Application.Impl-Windows.App.cppm"
		"Source/Private/Application.Impl-Windows.AppDataManager.cppm"
		"Source/Private/Application.Impl-Windows.Console.cppm"
		"Source/Private/Application.Impl-Windows.DefaultLogger.cppm"
		"Source/Private/Application.Impl-Windows.LoggerManager.cppm"
		"Source/Private/Application.Impl-Windows.PathManager.cppm"
		"Source/Private/Application.Impl-Windows.Process.cppm"
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
target_compile_definitions(PonyEngine.Application.Impl PRIVATE
	PONY_ENGINE_NAME=${PONY_ENGINE_NAME}
	PONY_ENGINE_VERSION_MAJOR=${PONY_ENGINE_VERSION_MAJOR}
	PONY_ENGINE_VERSION_MINOR=${PONY_ENGINE_VERSION_MINOR}
	PONY_ENGINE_VERSION_PATCH=${PONY_ENGINE_VERSION_PATCH}
	PONY_ENGINE_VERSION_TWEAK=${PONY_ENGINE_VERSION_TWEAK}
	PONY_ENGINE_TITLE=${PONY_ENGINE_TITLE}
	PONY_COMPANY_NAME=${PONY_COMPANY_NAME} 
	PONY_PROJECT_NAME=${PONY_PROJECT_NAME} 
	PONY_PROJECT_VERSION_MAJOR=${PONY_PROJECT_VERSION_MAJOR}
	PONY_PROJECT_VERSION_MINOR=${PONY_PROJECT_VERSION_MINOR}
	PONY_PROJECT_VERSION_PATCH=${PONY_PROJECT_VERSION_PATCH}
	PONY_PROJECT_VERSION_TWEAK=${PONY_PROJECT_VERSION_TWEAK}
	PONY_COMPANY_TITLE=${PONY_COMPANY_TITLE} 
	PONY_PROJECT_TITLE=${PONY_PROJECT_TITLE}
	PONY_ENGINE_ROOT_PATH=${PONY_ENGINE_ROOT_PATH}
	$<$<BOOL:${PONY_ENGINE_CREATE_CONSOLE}>:PONY_ENGINE_CREATE_CONSOLE>
	$<$<BOOL:${PONY_ENGINE_DEFAULT_LOGGER}>:PONY_ENGINE_DEFAULT_LOGGER>
	$<$<BOOL:${PONY_ENGINE_CONSOLE_LOG}>:PONY_ENGINE_CONSOLE_LOG>
	$<$<BOOL:${PONY_ENGINE_PLATFORM_CONSOLE_LOG}>:PONY_ENGINE_PLATFORM_CONSOLE_LOG>
	$<$<BOOL:${PONY_APP_ICON}>:PONY_APP_ICON=${PONY_APP_ICON}>
	$<$<BOOL:${PONY_APP_CURSOR}>:PONY_APP_CURSOR=${PONY_APP_CURSOR}>
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Application.Impl PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
	OUTPUT_NAME "${PONY_PROJECT_NAME}"
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Application.Impl PRIVATE
	PonyEngine.Application.Ext
	PonyEngine.Core
	PonyEngine.Log
)
