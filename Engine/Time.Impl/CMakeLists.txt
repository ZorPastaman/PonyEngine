message(STATUS "Configuring PonyEngine.Time.Impl")

message(VERBOSE "Configuring parameters")
set(PONY_ENGINE_TIME_ORDER "p" CACHE STRING "PonyEngine.Time.Impl module initialization order. Its first character must be in range [b-y].")
set(PONY_ENGINE_TIME_TICK_ORDER "0" CACHE STRING "PonyEngine.Time.Impl service tick order. It must be an int32 number.")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Time.Impl STATIC)

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.Time.Impl PUBLIC
	"Include/Public/Common"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Time.Impl PUBLIC
	"Source/Main.cpp"
)
target_sources(PonyEngine.Time.Impl PRIVATE
	"Source/Main.Impl.cpp"
)
target_sources(PonyEngine.Time.Impl PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Private/Time.Impl.cppm"
	"Source/Private/Time.Impl-TimeService.cppm"
	"Source/Private/Time.Impl-TimeServiceModule.cppm"
)

message(VERBOSE "Configuring defines")
pony_validate_module_order(PONY_ENGINE_TIME_ORDER)
pony_validate_tick_order(PONY_ENGINE_TIME_TICK_ORDER)
target_compile_definitions(PonyEngine.Time.Impl PUBLIC
	PONY_ENGINE_TIME_ORDER=${PONY_ENGINE_TIME_ORDER}
	PONY_ENGINE_TIME_TICK_ORDER=${PONY_ENGINE_TIME_TICK_ORDER}
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Time.Impl PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Time.Impl PUBLIC
	PonyEngine.Core
	PonyEngine.Application.Ext
)
if(NOT TARGET PonyEngine.Time)
	message(FATAL_ERROR "PonyEngine.Time wasn't configured")
endif()
target_link_libraries(PonyEngine.Time.Impl PUBLIC
	PonyEngine.Time
)
target_link_libraries(PonyEngine.Time.Impl PRIVATE
	PonyEngine.Log
)
