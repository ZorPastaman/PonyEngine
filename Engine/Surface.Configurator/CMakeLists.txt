message(STATUS "Configuring PonyEngine.Surface.Configurator")

message(VERBOSE "Validating settings")
if(NOT TARGET PonyEngine.Surface)
	message(FATAL_ERROR "PonyEngine.Surface wasn't configured")
endif()
if(NOT TARGET PonyEngine.Surface.Extension)
	message(FATAL_ERROR "PonyEngine.Surface.Extension wasn't configured")
endif()

if(NOT PONY_ENGINE_SURFACE_CONFIGURATOR_ORDER)
	message(FATAL_ERROR "PONY_ENGINE_SURFACE_CONFIGURATOR is set but PONY_ENGINE_SURFACE_CONFIGURATOR_ORDER isn't")
endif()
string(SUBSTRING "${PONY_ENGINE_SURFACE_CONFIGURATOR_ORDER}" 0 1 ORDER_FIRST_CHAR)
if(NOT ORDER_FIRST_CHAR MATCHES "^[b-y]$")
	message(FATAL_ERROR "PONY_ENGINE_SURFACE_CONFIGURATOR_ORDER is incorrect. Its first letter must be inside b-y range")
endif()

message(VERBOSE "Configuring target")
add_library(PonyEngine.Surface.Configurator STATIC)

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.Surface.Configurator PUBLIC
	"Include/Public/Common"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Surface.Configurator PUBLIC
	"Source/Main.cpp"
)
target_sources(PonyEngine.Surface.Configurator PRIVATE
	"Source/Main.Impl.cpp"
)
target_sources(PonyEngine.Surface.Configurator PRIVATE FILE_SET CXX_MODULES FILES
	"Source/Private/Surface.Configurator/Surface.Configurator.cppm"
	"Source/Private/Surface.Configurator/Surface.Configurator-SurfaceConfiguratorModule.cppm"
)

message(VERBOSE "Configuring defines")
target_compile_definitions(PonyEngine.Surface.Configurator PUBLIC
	PONY_ENGINE_SURFACE_CONFIGURATOR_ORDER=${PONY_ENGINE_SURFACE_CONFIGURATOR_ORDER}
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Surface.Configurator PROPERTIES 
	CXX_STANDARD 23
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Surface.Configurator PUBLIC
	PonyEngine.Core
	PonyEngine.Surface
	PonyEngine.Surface.Extension
)
