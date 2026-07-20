message(STATUS "Configuring PonyEngine.Application.Impl for Windows")

set(PONY_ENGINE_APPLICATION_MODE "GUI" CACHE STRING "Application mode. Must be Console or GUI.")
option(PONY_ENGINE_CREATE_CONSOLE "Enable console. Can be used only in GUI builds." OFF)

if(NOT PONY_ENGINE_APPLICATION_MODE STREQUAL "Console" AND NOT PONY_ENGINE_APPLICATION_MODE STREQUAL "GUI")
	message(FATAL_ERROR "Invalid PONY_ENGINE_APPLICATION_MODE: ${PONY_ENGINE_APPLICATION_MODE}. Must be Console or GUI")
endif()
if(PONY_ENGINE_APPLICATION_MODE STREQUAL "Console" AND PONY_ENGINE_CREATE_CONSOLE)
	message(FATAL_ERROR "PONY_ENGINE_CREATE_CONSOLE can't be TRUE if PONY_ENGINE_APPLICATION_MODE = Console")
endif()

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
	"Source/Main-Console.cppm"
	"Source/Main-ConsoleProcess.cppm"
	"Source/Main-GUIProcess.cppm"
	"Source/Main-Path.cppm"
	"Source/Main-Process.cppm"
)

message(VERBOSE "Configuring data")
configure_file("Data/Application.manifest.in" "${CMAKE_CURRENT_BINARY_DIR}/Generated/Data/Application.manifest")
target_sources(PonyEngine.Application.Impl PRIVATE 
	"${CMAKE_CURRENT_BINARY_DIR}/Generated/Data/Application.manifest"
)

message(VERBOSE "Configuring defines")
target_compile_definitions(PonyEngine.Application.Impl PRIVATE
	$<$<BOOL:${PONY_ENGINE_CREATE_CONSOLE}>:PONY_ENGINE_CREATE_CONSOLE>
	$<$<STREQUAL:${PONY_ENGINE_APPLICATION_MODE},Console>:PONY_ENGINE_APPLICATION_MODE_CONSOLE>
	$<$<STREQUAL:${PONY_ENGINE_APPLICATION_MODE},GUI>:PONY_ENGINE_APPLICATION_MODE_GUI>
)

message(VERBOSE "Setting properties")
if(PONY_ENGINE_APPLICATION_MODE STREQUAL "GUI")
	set_target_properties(PonyEngine.Application.Impl PROPERTIES
		WIN32_EXECUTABLE TRUE
	)
endif()
