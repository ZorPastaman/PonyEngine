message(STATUS "Configuring PonyEngine.Time.Main")

message(VERBOSE "Configuring parameters")
set(PONY_ENGINE_TIME_MAIN_ORDER "p" CACHE STRING "PonyEngine.Time.Main module initialization order. Its first character must be in range [b-y].")
set(PONY_ENGINE_TIME_MAIN_TICK_ORDER "0" CACHE STRING "PonyEngine.Time.Main service tick order. It must be an int32 number.")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Time.Main STATIC)

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.Time.Main PUBLIC
	"Include/Public/Common"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Time.Main PUBLIC
	"Source/Main.cpp"
)
target_sources(PonyEngine.Time.Main PRIVATE
	"Source/Main.Impl.cpp"
)
target_sources(PonyEngine.Time.Main PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Private/Time.Main.cppm"
	"Source/Private/Time.Main-TimeService.cppm"
	"Source/Private/Time.Main-TimeServiceModule.cppm"
)

message(VERBOSE "Configuring defines")
pony_validate_module_order(PONY_ENGINE_TIME_MAIN_ORDER)
pony_validate_tick_order(PONY_ENGINE_TIME_MAIN_TICK_ORDER)
target_compile_definitions(PonyEngine.Time.Main PUBLIC
	PONY_ENGINE_TIME_MAIN_ORDER=${PONY_ENGINE_TIME_MAIN_ORDER}
	PONY_ENGINE_TIME_MAIN_TICK_ORDER=${PONY_ENGINE_TIME_MAIN_TICK_ORDER}
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Time.Main PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Time.Main PUBLIC
	PonyEngine.Core
	PonyEngine.Application.Extension
)
if(NOT TARGET PonyEngine.Time)
	message(FATAL_ERROR "PonyEngine.Time wasn't configured")
endif()
target_link_libraries(PonyEngine.Time.Main PRIVATE
	PonyEngine.Time
	PonyEngine.Log
)
