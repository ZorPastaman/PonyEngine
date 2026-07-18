message(STATUS "Configuring PonyEngine.Application.Impl for Windows")

option(PONY_ENGINE_CREATE_CONSOLE "Enable console." OFF)
option(PONY_ENGINE_PLATFORM_CONSOLE_LOG "Enable logging to the platform console." ON)
set(PONY_ENGINE_APPLICATION_ICON "" CACHE FILEPATH "Application icon path. Must be .ico file. It's used only if PONY_ENGINE_APPLICATION_ICON_MODE is Custom.")
set(PONY_ENGINE_APPLICATION_CURSOR "" CACHE FILEPATH "Application cursor path. Must be .cur file. If not set, the Surface module is expected to create a default cursor.")

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.Application.Impl PRIVATE
	"Include/Private"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Application.Impl PRIVATE
	"Source/Launch.cpp"
)
target_sources(PonyEngine.Application.Impl PRIVATE FILE_SET CXX_MODULES BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}" FILES
	"Source/Main.cppm"
	"Source/Main-App.cppm"
	"Source/Main-AppDataManager.cppm"
	"Source/Main-Console.cppm"
	"Source/Main-DefaultLogger.cppm"
	
	"Source/Main-PathManager.cppm"
	"Source/Main-Process.cppm"
)

message(VERBOSE "Configuring data")
configure_file("Data/Application.manifest.in" "${CMAKE_CURRENT_BINARY_DIR}/Generated/Data/Application.manifest")
target_sources(PonyEngine.Application.Impl PRIVATE 
	"${CMAKE_CURRENT_BINARY_DIR}/Generated/Data/Application.manifest"
	"Data/Resource.rc"
)

message(VERBOSE "Configuring defines")
if(PONY_ENGINE_APPLICATION_ICON_MODE STREQUAL "Custom")
	set(PONY_ENGINE_APP_ICON ${PONY_ENGINE_APPLICATION_ICON})
elseif(PONY_ENGINE_APPLICATION_ICON_MODE STREQUAL "Default")
	set(PONY_ENGINE_APP_ICON "${PONY_ENGINE_APPLICATION_ICON_DEFAULT_PATH}/Windows/Logo.ico")
else()
	set(PONY_ENGINE_APP_ICON OFF)
endif()
target_compile_definitions(PonyEngine.Application.Impl PRIVATE
	$<$<BOOL:${PONY_ENGINE_CREATE_CONSOLE}>:PONY_ENGINE_CREATE_CONSOLE>
	$<$<BOOL:${PONY_ENGINE_PLATFORM_CONSOLE_LOG}>:PONY_ENGINE_PLATFORM_CONSOLE_LOG>
	$<$<BOOL:${PONY_ENGINE_APP_ICON}>:PONY_ENGINE_APPLICATION_ICON=${PONY_ENGINE_APP_ICON}>
	$<$<BOOL:${PONY_ENGINE_APPLICATION_CURSOR}>:PONY_ENGINE_APPLICATION_CURSOR=${PONY_ENGINE_APPLICATION_CURSOR}>
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Application.Impl PROPERTIES
	WIN32_EXECUTABLE TRUE
)
