message(STATUS "Configuring PonyEngine.Log.Impl")

if(NOT TARGET PonyEngine.Application)
	message(FATAL_ERROR "PonyEngine.Application wasn't configured")
endif()
if(NOT TARGET PonyEngine.Core)
	message(FATAL_ERROR "PonyEngine.Core wasn't configured")
endif()
if(NOT TARGET PonyEngine.Log)
	message(FATAL_ERROR "PonyEngine.Log wasn't configured")
endif()
if(NOT TARGET PonyEngine.Log.Ext)
	message(FATAL_ERROR "PonyEngine.Log.Ext wasn't configured")
endif()

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
	"Source/Main.cppm"
	"Source/Main-LogFiller.cppm"
	"Source/Main-LogService.cppm"
	"Source/Main-LogServicerModule.cppm"
	"Source/Main-LogTypeSymbol.cppm"
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
