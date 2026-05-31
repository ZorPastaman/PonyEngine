message(STATUS "Configuring PonyEngine.World.Impl")

message(VERBOSE "Configuring parameters")
set(PONY_ENGINE_WORLD_ORDER "p" CACHE STRING "PonyEngine.World.Impl module initialization order. Its first character must be in range [b-y].")

message(VERBOSE "Configuring target")
add_library(PonyEngine.World.Impl STATIC)

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.World.Impl PUBLIC
	"Include/Public"
)

message(VERBOSE "Configuring sources")
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

message(VERBOSE "Configuring defines")
pony_validate_module_order(PONY_ENGINE_WORLD_ORDER)
target_compile_definitions(PonyEngine.World.Impl PUBLIC
	PONY_ENGINE_WORLD_ORDER=${PONY_ENGINE_WORLD_ORDER}
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.World.Impl PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
if(NOT TARGET PonyEngine.World)
	message(FATAL_ERROR "PonyEngine.World wasn't configured")
endif()
target_link_libraries(PonyEngine.World.Impl PUBLIC
	PonyEngine.Application.Ext
)
target_link_libraries(PonyEngine.World.Impl PRIVATE
	PonyEngine.World
	PonyEngine.Core
	PonyEngine.Log
)
