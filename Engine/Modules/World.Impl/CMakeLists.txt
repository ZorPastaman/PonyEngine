message(STATUS "Configuring PonyEngine.World.Impl")

if(NOT TARGET PonyEngine.Application)
	message(FATAL_ERROR "PonyEngine.Application wasn't configured")
endif()
if(NOT TARGET PonyEngine.Core)
	message(FATAL_ERROR "PonyEngine.Core wasn't configured")
endif()
if(NOT TARGET PonyEngine.Log)
	message(FATAL_ERROR "PonyEngine.Log wasn't configured")
endif()
if(NOT TARGET PonyEngine.World)
	message(FATAL_ERROR "PonyEngine.World wasn't configured")
endif()

set(PONY_ENGINE_WORLD_ORDER "p" CACHE STRING "PonyEngine.World.Impl module initialization order. Its first character must be in range [b-y].")

add_library(PonyEngine.World.Impl STATIC)

target_include_directories(PonyEngine.World.Impl PUBLIC
	"Include/Public"
)

target_sources(PonyEngine.World.Impl PUBLIC
	"Source/Launch.cpp"
)
target_sources(PonyEngine.World.Impl PRIVATE
	"Source/Launch.Impl.cpp"
)
target_sources(PonyEngine.World.Impl PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Main.cppm"
	"Source/Main-ComponentTable.cppm"
	"Source/Main-ObjectTable.cppm"
	"Source/Main-TypeRegistry.cppm"
	"Source/Main-World.cppm"
	"Source/Main-WorldService.cppm"
	"Source/Main-WorldServiceModule.cppm"
)

pony_validate_module_order(PONY_ENGINE_WORLD_ORDER)
target_compile_definitions(PonyEngine.World.Impl PUBLIC
	PONY_ENGINE_WORLD_ORDER=${PONY_ENGINE_WORLD_ORDER}
)

set_target_properties(PonyEngine.World.Impl PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
)

target_link_libraries(PonyEngine.World.Impl PUBLIC
	PonyEngine.Application
)
target_link_libraries(PonyEngine.World.Impl PRIVATE
	PonyEngine.Core
	PonyEngine.Log
	PonyEngine.World
)
