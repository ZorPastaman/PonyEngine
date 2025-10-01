message(STATUS "Configuring PonyEngine.Path.Configurator")

message(VERBOSE "Validating settings")
if(NOT TARGET PonyEngine.Path)
	message(FATAL_ERROR "PonyEngine.Path wasn't configured")
endif()
if(NOT TARGET PonyEngine.Path.Extension)
	message(FATAL_ERROR "PonyEngine.Path.Extension wasn't configured")
endif()

if(NOT PONY_ENGINE_PATH_CONFIGURATOR_ORDER)
	message(FATAL_ERROR "PONY_ENGINE_PATH_CONFIGURATOR is set but PONY_ENGINE_PATH_CONFIGURATOR_ORDER isn't")
endif()
string(SUBSTRING "${PONY_ENGINE_PATH_CONFIGURATOR_ORDER}" 0 1 ORDER_FIRST_CHAR)
if(NOT ORDER_FIRST_CHAR MATCHES "^[b-y]$")
	message(FATAL_ERROR "PONY_ENGINE_PATH_CONFIGURATOR_ORDER is incorrect. Its first letter must be inside b-y range")
endif()

if(PONY_ENGINE_PATH_ROOT_PATH)
	if(IS_ABSOLUTE PONY_ENGINE_PATH_ROOT_PATH)
		message(FATAL_ERROR "PONY_ENGINE_PATH_ROOT_PATH isn't relative")
	endif()
	if(NOT PONY_ENGINE_PATH_ROOT_PATH MATCHES "^[A-Za-z0-9._/-]+$")
		message(FATAL_ERROR "PONY_ENGINE_PATH_ROOT_PATH contains invalid symbols")
	endif()
	foreach(path_component IN LISTS PONY_ENGINE_PATH_ROOT_PATH)
		string(TOLOWER "${path_component}" path_component_lower)
		if("${path_component_lower}" MATCHES "^(con|prn|aux|nul|com[1-9]|lpt[1-9])(\\..*)?$")
			message(FATAL_ERROR "PONY_ENGINE_PATH_ROOT_PATH contains invalid component names")
		endif()
	endforeach()
else()
	set(PONY_ENGINE_PATH_ROOT_PATH "")
endif()

if(PONY_ENGINE_PATH_LOG_PATH)
	if(IS_ABSOLUTE PONY_ENGINE_PATH_LOG_PATH)
		message(FATAL_ERROR "PONY_ENGINE_PATH_LOG_PATH isn't relative")
	endif()
	if(NOT PONY_ENGINE_PATH_LOG_PATH MATCHES "^[A-Za-z0-9._/-]+$")
		message(FATAL_ERROR "PONY_ENGINE_PATH_LOG_PATH contains invalid symbols")
	endif()
	foreach(path_component IN LISTS PONY_ENGINE_PATH_LOG_PATH)
		string(TOLOWER "${path_component}" path_component_lower)
		if("${path_component_lower}" MATCHES "^(con|prn|aux|nul|com[1-9]|lpt[1-9])(\\..*)?$")
			message(FATAL_ERROR "PONY_ENGINE_PATH_LOG_PATH contains invalid component names")
		endif()
	endforeach()
else()
	set(PONY_ENGINE_PATH_LOG_PATH "")
endif()

message(VERBOSE "Configuring target")
add_library(PonyEngine.Path.Configurator STATIC)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Path.Configurator PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Private/Path.Configurator/Path.Configurator.cppm"
	"Source/Private/Path.Configurator/Path.Configurator-Utility.cppm"
)

if(PONY_WINDOWS)
	message(VERBOSE "Configuring headers for Windows")
	target_include_directories(PonyEngine.Path.Configurator PUBLIC
		"Include/Public/Windows"
	)

	message(VERBOSE "Configuring sources for Windows")
	target_sources(PonyEngine.Path.Configurator PUBLIC
		"Source/Main.Windows.cpp"
	)
	target_sources(PonyEngine.Path.Configurator PRIVATE
		"Source/Main.Windows.Impl.cpp"
	)
	target_sources(PonyEngine.Path.Configurator PRIVATE FILE_SET CXX_MODULES FILES 
		"Source/Private/Path.Configurator/Windows/Path.Configurator.Windows.cppm"
		"Source/Private/Path.Configurator/Windows/Path.Configurator.Windows-PathConfiguratorModule.cppm"
	)
endif()

message(VERBOSE "Configuring defines")
target_compile_definitions(PonyEngine.Path.Configurator PUBLIC
	PONY_ENGINE_PATH_CONFIGURATOR_ORDER=${PONY_ENGINE_PATH_CONFIGURATOR_ORDER}
	PONY_ENGINE_PATH_ROOT_PATH=${PONY_ENGINE_PATH_ROOT_PATH} PONY_ENGINE_PATH_LOG_PATH=${PONY_ENGINE_PATH_LOG_PATH}
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Path.Configurator PROPERTIES 
	CXX_STANDARD 23
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Path.Configurator PUBLIC
	PonyEngine.Core
	PonyEngine.Path
	PonyEngine.Path.Extension
)
