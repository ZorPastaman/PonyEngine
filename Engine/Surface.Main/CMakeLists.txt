message(STATUS "Configuring PonyEngine.Surface.Main")

message(VERBOSE "Configuring parameters")
set(PONY_ENGINE_SURFACE_MAIN_ORDER "p" CACHE STRING "PonyEngine.Surface.Main module initialization order. Its first character must be in range [b-y].")

message(VERBOSE "Configuring target")
add_library(PonyEngine.Surface.Main STATIC)

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.Surface.Main PUBLIC
	"Include/Public/Common"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Surface.Main PUBLIC
	"Source/Main.cpp"
)
target_sources(PonyEngine.Surface.Main PRIVATE
	"Source/Main.Impl.cpp"
)
target_sources(PonyEngine.Surface.Main PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Private/Surface.Main/Surface.Main.cppm"
	"Source/Private/Surface.Main/Surface.Main-MessageHandler.cppm"
	"Source/Private/Surface.Main/Surface.Main-SurfaceService.cppm"
	"Source/Private/Surface.Main/Surface.Main-SurfaceServiceModule.cppm"
	"Source/Private/Surface.Main/Surface.Main-WindowClass.cppm"
)

message(VERBOSE "Configuring defines")
pony_validate_module_order(PONY_ENGINE_SURFACE_MAIN_ORDER)
target_compile_definitions(PonyEngine.Surface.Main PUBLIC
	PONY_ENGINE_SURFACE_MAIN_ORDER=${PONY_ENGINE_SURFACE_MAIN_ORDER}
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Surface.Main PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Surface.Main PUBLIC
	PonyEngine.Core
	PonyEngine.Application.Extension
)
if(NOT TARGET PonyEngine.Surface)
	message(FATAL_ERROR "PonyEngine.Surface wasn't configured")
endif()
target_link_libraries(PonyEngine.Surface.Main PRIVATE
	PonyEngine.Surface
	PonyEngine.Log
)
