message(STATUS "Configuring PonyEngine.Surface.Main")

message(VERBOSE "Validating settings")
if(NOT TARGET PonyEngine.Surface)
	message(FATAL_ERROR "PonyEngine.Surface wasn't configured")
endif()

pony_validate_module_order(PONY_ENGINE_SURFACE_MAIN_ORDER)

if(PONY_ENGINE_SURFACE_BACKGROUND_COLOR)
	if(${PONY_ENGINE_SURFACE_BACKGROUND_COLOR} MATCHES "^[ \t]*([0-9]+)[ \t]*,[ \t]*([0-9]+)[ \t]*,[ \t]*([0-9]+)[ \t]*$")
		set(R ${CMAKE_MATCH_1})
		set(G ${CMAKE_MATCH_2})
		set(B ${CMAKE_MATCH_3})
		if(R LESS 0 OR R GREATER 255 OR G LESS 0 OR G GREATER 255 OR B LESS 0 OR B GREATER 255)
			message(FATAL_ERROR "PONY_ENGINE_SURFACE_BACKGROUND_COLOR is invalid")
		endif()
	else()
		message(FATAL_ERROR "PONY_ENGINE_SURFACE_BACKGROUND_COLOR is invalid")
	endif()
endif()

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
	"Source/Private/Surface.Main/Surface.Main-ParamProvider.cppm"
	"Source/Private/Surface.Main/Surface.Main-SurfaceService.cppm"
	"Source/Private/Surface.Main/Surface.Main-SurfaceServiceModule.cppm"
	"Source/Private/Surface.Main/Surface.Main-WindowClass.cppm"
)

message(VERBOSE "Configuring defines")
target_compile_definitions(PonyEngine.Surface.Main PUBLIC
	PONY_ENGINE_SURFACE_MAIN_ORDER=${PONY_ENGINE_SURFACE_MAIN_ORDER}
)
if(PONY_ENGINE_SURFACE_BACKGROUND_COLOR)
	target_compile_definitions(PonyEngine.Surface.Main PRIVATE
		PONY_ENGINE_SURFACE_BACKGROUND_COLOR=${PONY_ENGINE_SURFACE_BACKGROUND_COLOR}
	)
endif()

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Surface.Main PROPERTIES 
	CXX_STANDARD 23
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Surface.Main PUBLIC
	PonyEngine.Core
	PonyEngine.Application.Extension
)
target_link_libraries(PonyEngine.Surface.Main PRIVATE
	PonyEngine.Surface
	PonyEngine.Log
)
