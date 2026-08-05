message(STATUS "Configuring PonyEngine.Application.Impl for Windows")

set(PONY_ENGINE_APPLICATION_MODE "GUI" CACHE STRING "Application mode. Must be Console or GUI.")
option(PONY_ENGINE_APPLICATION_CREATE_CONSOLE "Enable console. Can be used only in GUI builds." OFF)
set(PONY_ENGINE_APPLICATION_PROCESS_PRIORITY "ABOVE_NORMAL_PRIORITY_CLASS" CACHE STRING "Application process priority. Must be DWORD or predefined priority class.")
set(PONY_ENGINE_APPLICATION_NEXT_FRAME_BUSY_SPIN_LENGTH "0.001" CACHE STRING "Amount of time in seconds that is waited on busy spin. All other time before it is waited on thread sleep. Must be double.")
option(PONY_ENGINE_APPLICATION_ADD_DEFAULT_MANIFEST "Add default manifest." ON)
set(PONY_ENGINE_APPLICATION_SUPPORTED_OS "8e0f7a12-bfb3-4fe8-b9a5-48fd50a15a9a" CACHE STRING "Supported OS GUID. By default, it corresponds to Windows 10/11.")

if(NOT PONY_ENGINE_APPLICATION_MODE STREQUAL "Console" AND NOT PONY_ENGINE_APPLICATION_MODE STREQUAL "GUI")
	message(FATAL_ERROR "Invalid PONY_ENGINE_APPLICATION_MODE: ${PONY_ENGINE_APPLICATION_MODE}. Must be Console or GUI")
endif()
if(PONY_ENGINE_APPLICATION_MODE STREQUAL "Console" AND PONY_ENGINE_APPLICATION_CREATE_CONSOLE)
	message(FATAL_ERROR "PONY_ENGINE_APPLICATION_CREATE_CONSOLE can't be TRUE if PONY_ENGINE_APPLICATION_MODE = Console")
endif()

include("CMake/Resource.cmake")
include("CMake/ThreadRole.cmake")

target_sources(PonyEngine.Application.Impl PRIVATE
	"Source/Launch.cpp"
)
target_sources(PonyEngine.Application.Impl PRIVATE FILE_SET CXX_MODULES BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}" FILES
	"Source/Main.cppm"
	"Source/Main-CommandLine.cppm"
	"Source/Main-ConsoleProcess.cppm"
	"Source/Main-Context.cppm"
	"Source/Main-GUIProcess.cppm"
	"Source/Main-Path.cppm"
	"Source/Main-Process.cppm"
	"Source/Main-ThreadControl.cppm"
	"Source/Main-Timer.cppm"
)

if(PONY_ENGINE_APPLICATION_ADD_DEFAULT_MANIFEST)
	set(MANIFEST_PATH "${CMAKE_CURRENT_BINARY_DIR}/Generated/Data/Application.manifest")
	configure_file("Data/Application.manifest.in" "${MANIFEST_PATH}")
	target_sources(PonyEngine.Application.Impl PRIVATE "${MANIFEST_PATH}")
endif()

target_compile_definitions(PonyEngine.Application.Impl PRIVATE
	$<$<BOOL:${PONY_ENGINE_APPLICATION_CREATE_CONSOLE}>:PONY_ENGINE_APPLICATION_CREATE_CONSOLE>
	$<$<STREQUAL:${PONY_ENGINE_APPLICATION_MODE},Console>:PONY_ENGINE_APPLICATION_MODE_CONSOLE>
	$<$<STREQUAL:${PONY_ENGINE_APPLICATION_MODE},GUI>:PONY_ENGINE_APPLICATION_MODE_GUI>
	PONY_ENGINE_APPLICATION_PROCESS_PRIORITY=${PONY_ENGINE_APPLICATION_PROCESS_PRIORITY}
	PONY_ENGINE_APPLICATION_NEXT_FRAME_BUSY_SPIN_LENGTH=${PONY_ENGINE_APPLICATION_NEXT_FRAME_BUSY_SPIN_LENGTH}
)

if(PONY_ENGINE_APPLICATION_MODE STREQUAL "GUI")
	set_target_properties(PonyEngine.Application.Impl PROPERTIES
		WIN32_EXECUTABLE TRUE
	)
endif()

target_link_libraries(PonyEngine.Application.Impl PRIVATE
	avrt.lib
)
