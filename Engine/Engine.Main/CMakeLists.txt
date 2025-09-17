message(STATUS "Configuring PonyEngine.Engine.Main")

message(VERBOSE "Validating settings")
if(NOT TARGET PonyEngine.Engine.Extension)
	message(FATAL_ERROR "PonyEngine.Engine.Extension wasn't configured")
endif()

if(NOT PONY_ENGINE_ENGINE_MAIN_ORDER)
	message(FATAL_ERROR "PONY_ENGINE_ENGINE_MAIN is set but PONY_ENGINE_ENGINE_MAIN_ORDER isn't")
endif()
string(SUBSTRING "${PONY_ENGINE_ENGINE_MAIN_ORDER}" 0 1 ORDER_FIRST_CHAR)
if(NOT ORDER_FIRST_CHAR MATCHES "^[b-y]$")
	message(FATAL_ERROR "PONY_ENGINE_ENGINE_MAIN_ORDER is incorrect. Its first letter must be inside b-y range")
endif()
if(${PONY_ENGINE_ENGINE_MAIN_TICK_ORDER} STREQUAL "")
	message(FATAL_ERROR "PONY_ENGINE_ENGINE_MAIN is set but PONY_ENGINE_ENGINE_MAIN_TICK_ORDER isn't")
endif()
if(NOT PONY_ENGINE_ENGINE_MAIN_TICK_ORDER MATCHES "^-?[0-9]+$")
	message(FATAL_ERROR "PONY_ENGINE_ENGINE_MAIN_TICK_ORDER isn't a number")
endif()

message(VERBOSE "Configuring target")
add_library(PonyEngine.Engine.Main STATIC)

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.Engine.Main PUBLIC
	"Include/Public/Common"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Engine.Main PUBLIC
	"Source/Main.cpp"
)
target_sources(PonyEngine.Engine.Main PRIVATE
	"Source/Main.Impl.cpp"
)
target_sources(PonyEngine.Engine.Main PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Private/Engine.Main/Engine.Main.cppm"
	"Source/Private/Engine.Main/Engine.Main-Engine.cppm"
	"Source/Private/Engine.Main/Engine.Main-EngineFactory.cppm"
	"Source/Private/Engine.Main/Engine.Main-EngineLogger.cppm"
	"Source/Private/Engine.Main/Engine.Main-EngineModule.cppm"
	"Source/Private/Engine.Main/Engine.Main-SystemManager.cppm"
)

message(VERBOSE "Configuring defines")
target_compile_definitions(PonyEngine.Engine.Main PUBLIC
	PONY_ENGINE_ENGINE_MAIN_ORDER=${PONY_ENGINE_ENGINE_MAIN_ORDER} PONY_ENGINE_ENGINE_MAIN_TICK_ORDER=${PONY_ENGINE_ENGINE_MAIN_TICK_ORDER}
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Engine.Main PROPERTIES 
	CXX_STANDARD 23
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Engine.Main PUBLIC
	PonyEngine.Core
	PonyEngine.Engine.Extension
)
