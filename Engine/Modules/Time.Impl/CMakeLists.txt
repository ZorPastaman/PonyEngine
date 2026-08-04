message(STATUS "Configuring PonyEngine.Time.Impl")

if(NOT TARGET PonyEngine.Application)
	message(FATAL_ERROR "PonyEngine.Application wasn't configured")
endif()
if(NOT TARGET PonyEngine.Core)
	message(FATAL_ERROR "PonyEngine.Core wasn't configured")
endif()
if(NOT TARGET PonyEngine.Log)
	message(FATAL_ERROR "PonyEngine.Log wasn't configured")
endif()
if(NOT TARGET PonyEngine.Time)
	message(FATAL_ERROR "PonyEngine.Time wasn't configured")
endif()

set(PONY_ENGINE_TIME_ORDER "p" CACHE STRING "PonyEngine.Time.Impl module initialization order. Its first character must be in range [b-y].")
set(PONY_ENGINE_TIME_TICK_ORDER "0" CACHE STRING "PonyEngine.Time.Impl service tick order. It must be an int32 number.")
set(PONY_ENGINE_TIME_DELTA_TIME_CAP "1.0" CACHE STRING "PonyEngine.Time.Impl service initial delta time cap in seconds. It must be a double number.")
set(PONY_ENGINE_TIME_SCALE "1.0" CACHE STRING "PonyEngine.Time.Impl service initial scale. It must be a double number.")
set(PONY_ENGINE_TIME_STEP_PERIOD "1.0 / 60.0" CACHE STRING "PonyEngine.Time.Impl service initial step period in seconds. It must be a double number.")

add_library(PonyEngine.Time.Impl STATIC)

target_include_directories(PonyEngine.Time.Impl PUBLIC
	"Include/Public"
)

target_sources(PonyEngine.Time.Impl PUBLIC
	"Source/Launch.cpp"
)
target_sources(PonyEngine.Time.Impl PRIVATE
	"Source/Launch.Impl.cpp"
)
target_sources(PonyEngine.Time.Impl PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Main.cppm"
	"Source/Main-TimeService.cppm"
	"Source/Main-TimeServiceModule.cppm"
)

pony_validate_module_order(PONY_ENGINE_TIME_ORDER)
pony_validate_tick_order(PONY_ENGINE_TIME_TICK_ORDER)
target_compile_definitions(PonyEngine.Time.Impl PUBLIC
	PONY_ENGINE_TIME_ORDER=${PONY_ENGINE_TIME_ORDER}
)
target_compile_definitions(PonyEngine.Time.Impl PRIVATE
	PONY_ENGINE_TIME_TICK_ORDER=${PONY_ENGINE_TIME_TICK_ORDER}
	PONY_ENGINE_TIME_DELTA_TIME_CAP=${PONY_ENGINE_TIME_DELTA_TIME_CAP}
	PONY_ENGINE_TIME_SCALE=${PONY_ENGINE_TIME_SCALE}
	PONY_ENGINE_TIME_STEP_PERIOD=${PONY_ENGINE_TIME_STEP_PERIOD}
)

set_target_properties(PonyEngine.Time.Impl PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.Time.Impl PUBLIC
	PonyEngine.Application
)
target_link_libraries(PonyEngine.Time.Impl PRIVATE
	PonyEngine.Core
	PonyEngine.Log
	PonyEngine.Time
)
