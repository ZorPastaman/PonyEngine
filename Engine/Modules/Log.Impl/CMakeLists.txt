message(STATUS "Configuring PonyEngine.Log.Impl feature module")

set(PONY_ENGINE_LOG_ORDER "p" CACHE STRING "PonyEngine.Log.Impl module initialization order. Its first character must be in range [b-y].")

add_library(PonyEngine.Log.Impl STATIC)

target_include_directories(PonyEngine.Log.Impl PUBLIC
	"Include/Public"
)

target_sources(PonyEngine.Log.Impl PUBLIC
	"Source/Launch.cpp"
)
target_sources(PonyEngine.Log.Impl PRIVATE
	"Source/Launch.Impl.cpp"
)
target_sources(PonyEngine.Log.Impl PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Log.cppm"
	"Source/Log-LogFiller.cppm"
	"Source/Log-LogService.cppm"
	"Source/Log-LogServicerModule.cppm"
	"Source/Log-LogTypeSymbol.cppm"
)

pony_validate_module_order(PONY_ENGINE_LOG_ORDER)
target_compile_definitions(PonyEngine.Log.Impl PUBLIC 
	PONY_ENGINE_LOG_ORDER=${PONY_ENGINE_LOG_ORDER}
)

set_target_properties(PonyEngine.Log.Impl PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.Log.Impl PUBLIC
	PonyEngine.Application
)
target_link_libraries(PonyEngine.Log.Impl PRIVATE
	PonyEngine.Core
	PonyEngine.Log
	PonyEngine.Log.Ext
)
