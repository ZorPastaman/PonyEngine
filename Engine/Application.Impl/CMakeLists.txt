message(STATUS "Configuring PonyEngine.Application.Impl")

message(VERBOSE "Configuring parameters")
option(PONY_ENGINE_DEFAULT_LOGGER "Enable default logger. It logs everything to a console." ON)
option(PONY_ENGINE_CONSOLE_LOG "Enable standard C++ console." ON)

message(VERBOSE "Configuring target")
add_executable(PonyEngine.Application.Impl)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Application.Impl PRIVATE FILE_SET CXX_MODULES FILES
	"Source/Private/Main.cppm"
	"Source/Private/Main-ConsoleUtility.cppm"
	"Source/Private/Main-DefaultLogger.cppm"
	"Source/Private/Main-ExitCodes.cppm"
	"Source/Private/Main-FlowManager.cppm"
	"Source/Private/Main-IdentityUtility.cppm"
	"Source/Private/Main-InterfaceContainer.cppm"
	"Source/Private/Main-LoggerManager.cppm"
	"Source/Private/Main-ModuleDataContainer.cppm"
	"Source/Private/Main-ModuleManager.cppm"
	"Source/Private/Main-PathUtility.cppm"
	"Source/Private/Main-ServiceContainer.cppm"
	"Source/Private/Main-ServiceManager.cppm"
	"Source/Private/Main-ThreadManager.cppm"
	"Source/Private/Main-TickableServiceInfo.cppm"
)

message(VERBOSE "Configuring defines")
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
	$<$<BOOL:${PONY_ENGINE_DEFAULT_LOGGER}>:PONY_ENGINE_DEFAULT_LOGGER>
	$<$<BOOL:${PONY_ENGINE_CONSOLE_LOG}>:PONY_ENGINE_CONSOLE_LOG>
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
