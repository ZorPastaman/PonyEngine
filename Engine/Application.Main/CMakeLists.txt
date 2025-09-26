message(STATUS "Configuring PonyEngine.Application.Main")

message(VERBOSE "Validating settings")
if(PONY_ENGINE_CREATE_CONSOLE)
	if(NOT PONY_WINCORE)
		message(FATAL_ERROR "PONY_ENGINE_CREATE_CONSOLE is set but the current platform doesn't support a console")
	endif()
endif()

if(NOT PONY_ENGINE_MESSAGE_LOOP_ORDER)
	message(FATAL_ERROR "PONY_ENGINE_APPLICATION_MAIN is set but PONY_ENGINE_MESSAGE_LOOP_ORDER isn't")
endif()
string(SUBSTRING "${PONY_ENGINE_MESSAGE_LOOP_ORDER}" 0 1 MESSAGE_LOOP_ORDER_FIRST_CHAR)
if(NOT MESSAGE_LOOP_ORDER_FIRST_CHAR MATCHES "^[b-y]$")
	message(FATAL_ERROR "PONY_ENGINE_MESSAGE_LOOP_ORDER is incorrect. Its first letter must be inside b-y range")
endif()
if(${PONY_ENGINE_MESSAGE_LOOP_TICK_ORDER} STREQUAL "")
	message(FATAL_ERROR "PONY_ENGINE_APPLICATION_MAIN is set but PONY_ENGINE_MESSAGE_LOOP_TICK_ORDER isn't")
endif()
if(NOT PONY_ENGINE_MESSAGE_LOOP_TICK_ORDER MATCHES "^-?[0-9]+$")
	message(FATAL_ERROR "PONY_ENGINE_MESSAGE_LOOP_TICK_ORDER isn't a number")
endif()
if(NOT PONY_ENGINE_MAIN_DATA_ORDER)
	message(FATAL_ERROR "PONY_ENGINE_APPLICATION_MAIN is set but PONY_ENGINE_MAIN_DATA_ORDER isn't")
endif()
string(SUBSTRING "${PONY_ENGINE_MAIN_DATA_ORDER}" 0 1 MAIN_DATA_ORDER_FIRST_CHAR)
if(NOT MAIN_DATA_ORDER_FIRST_CHAR MATCHES "^[b-y]$")
	message(FATAL_ERROR "PONY_ENGINE_MAIN_DATA_ORDER is incorrect. Its first letter must be inside b-y range")
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
	"Source/Private/Application.Main/Application.Main-ServiceManager.cppm"
)

if(PONY_WINDOWS)
	message(VERBOSE "Configuring sources for Windows")
	target_sources(PonyEngine.Application.Main PRIVATE FILE_SET CXX_MODULES FILES 
		"Source/Private/Application.Main/Windows/Application.Main.Windows.cppm"
		"Source/Private/Application.Main/Windows/Application.Main.Windows-Console.cppm"
		"Source/Private/Application.Main/Windows/Application.Main.Windows-MainDataService.cppm"
		"Source/Private/Application.Main/Windows/Application.Main.Windows-MainDataServiceFactory.cppm"
		"Source/Private/Application.Main/Windows/Application.Main.Windows-MainDataServiceModule.cppm"
		"Source/Private/Application.Main/Windows/Application.Main.Windows-MessageLoopService.cppm"
		"Source/Private/Application.Main/Windows/Application.Main.Windows-MessageLoopServiceFactory.cppm"
		"Source/Private/Application.Main/Windows/Application.Main.Windows-MessageLoopServiceModule.cppm"
		"Source/Private/Application.Main/Windows/Application.Main.Windows-Process.cppm"
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
if(PONY_ENGINE_DEFAULT_LOGGER)
	target_compile_definitions(PonyEngine.Application.Main PRIVATE PONY_ENGINE_DEFAULT_LOGGER)
endif()
target_compile_definitions(PonyEngine.Application.Main PRIVATE 
	PONY_COMPANY_NAME=${PONY_COMPANY_NAME} PONY_PROJECT_NAME=${PONY_PROJECT_NAME} PONY_PROJECT_VERSION=${PONY_PROJECT_VERSION}
	PONY_COMPANY_TITLE=${PONY_COMPANY_TITLE} PONY_PROJECT_TITLE=${PONY_PROJECT_TITLE}
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
