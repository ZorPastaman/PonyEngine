message(STATUS "Configuring PonyEngine.Application.Impl for Windows")

option(PONY_ENGINE_CREATE_CONSOLE "Enable console." OFF)
option(PONY_ENGINE_PLATFORM_CONSOLE_LOG "Enable platform console." ON)
set(PONY_ENGINE_ROOT_PATH "" CACHE STRING "Root path. It must be relative to an executable directory, and the folder must exist at runtime. Empty path is valid.")
set(PONY_APP_ICON "" CACHE FILEPATH "Application icon path. Must be .ico file. If it's '<Default>', the engine icon is used.")
set(PONY_APP_CURSOR "" CACHE FILEPATH "Application cursor path. Must be .cur file. If not set, the Surface module is expected to create a default cursor.")

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.Application.Impl PRIVATE
	"Include/Private"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Application.Impl PRIVATE
	"Source/Main.cpp"
)
target_sources(PonyEngine.Application.Impl PRIVATE FILE_SET CXX_MODULES BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}" FILES
	"Source/Private/Main.cppm"
	"Source/Private/Main-App.cppm"
	"Source/Private/Main-AppDataManager.cppm"
	"Source/Private/Main-Console.cppm"
	"Source/Private/Main-DefaultLogger.cppm"
	"Source/Private/Main-LoggerManager.cppm"
	"Source/Private/Main-PathManager.cppm"
	"Source/Private/Main-Process.cppm"
)

message(VERBOSE "Configuring data")
configure_file("Data/Application.manifest.in" "${CMAKE_CURRENT_BINARY_DIR}/Generated/Data/Application.manifest")
target_sources(PonyEngine.Application.Impl PRIVATE 
	"${CMAKE_CURRENT_BINARY_DIR}/Generated/Data/Application.manifest"
	"Data/Resource.rc"
)

message(VERBOSE "Configuring defines")
if(PONY_ENGINE_ROOT_PATH)
	pony_validate_path(PONY_ENGINE_ROOT_PATH false true)
else()
	set(PONY_ENGINE_ROOT_PATH "")
endif()
if(PONY_APP_ICON STREQUAL "<Default>")
	set(PONY_APP_ICON "${PONY_ROOT}/Logo/Windows/Logo.ico")
endif()
target_compile_definitions(PonyEngine.Application.Impl PRIVATE
	PONY_ENGINE_ROOT_PATH=${PONY_ENGINE_ROOT_PATH}
	$<$<BOOL:${PONY_ENGINE_CREATE_CONSOLE}>:PONY_ENGINE_CREATE_CONSOLE>
	$<$<BOOL:${PONY_ENGINE_PLATFORM_CONSOLE_LOG}>:PONY_ENGINE_PLATFORM_CONSOLE_LOG>
	$<$<BOOL:${PONY_APP_ICON}>:PONY_APP_ICON=${PONY_APP_ICON}>
	$<$<BOOL:${PONY_APP_CURSOR}>:PONY_APP_CURSOR=${PONY_APP_CURSOR}>
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Application.Impl PROPERTIES
	WIN32_EXECUTABLE TRUE
)
