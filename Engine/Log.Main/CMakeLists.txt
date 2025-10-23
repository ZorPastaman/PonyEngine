message(STATUS "Configuring PonyEngine.Log.Main")

message(VERBOSE "Configuring parameters")
set(PONY_ENGINE_LOG_MAIN_ORDER "p" CACHE STRING "PonyEngine.Log.Main module initialization order. Its first character must be in range [b-y].")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Log.Main STATIC)

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.Log.Main PUBLIC
	"Include/Public/Common"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Log.Main PUBLIC
	"Source/Main.cpp"
)
target_sources(PonyEngine.Log.Main PRIVATE
	"Source/Main.Impl.cpp"
)
target_sources(PonyEngine.Log.Main PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Private/Log.Main/Log.Main.cppm"
	"Source/Private/Log.Main/Log.Main-Logger.cppm"
	"Source/Private/Log.Main/Log.Main-LoggerModule.cppm"
)

message(VERBOSE "Configuring defines")
pony_validate_module_order(PONY_ENGINE_LOG_MAIN_ORDER)
target_compile_definitions(PonyEngine.Log.Main PUBLIC 
	PONY_ENGINE_LOG_MAIN_ORDER=${PONY_ENGINE_LOG_MAIN_ORDER}
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Log.Main PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Log.Main PUBLIC
	PonyEngine.Core
	PonyEngine.Application.Extension
)
if(NOT TARGET PonyEngine.Log.Extension)
	message(FATAL_ERROR "PonyEngine.Log.Extension wasn't configured")
endif()
target_link_libraries(PonyEngine.Log.Main PRIVATE
	PonyEngine.Log
	PonyEngine.Log.Extension
)
