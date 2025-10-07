message(STATUS "Configuring PonyEngine.Surface.Main")

message(VERBOSE "Validating settings")
if(NOT TARGET PonyEngine.Surface)
	message(FATAL_ERROR "PonyEngine.Surface wasn't configured")
endif()

if(NOT PONY_ENGINE_SURFACE_MAIN_ORDER)
	message(FATAL_ERROR "PONY_ENGINE_SURFACE_MAIN is set but PONY_ENGINE_SURFACE_MAIN_ORDER isn't")
endif()
string(SUBSTRING "${PONY_ENGINE_SURFACE_MAIN_ORDER}" 0 1 ORDER_FIRST_CHAR)
if(NOT ORDER_FIRST_CHAR MATCHES "^[b-y]$")
	message(FATAL_ERROR "PONY_ENGINE_SURFACE_MAIN_ORDER is incorrect. Its first letter must be inside b-y range")
endif()

message(VERBOSE "Configuring target")
add_library(PonyEngine.Surface.Main STATIC)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Surface.Main PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Private/Surface.Main/Surface.Main.cppm"
)

if(PONY_WINDOWS)
	message(VERBOSE "Configuring headers for Windows")
	target_include_directories(PonyEngine.Surface.Main PUBLIC
		"Include/Public/Windows"
	)

	message(VERBOSE "Configuring sources for Windows")
	target_sources(PonyEngine.Surface.Main PUBLIC
		"Source/Main.Windows.cpp"
	)
	target_sources(PonyEngine.Surface.Main PRIVATE
		"Source/Main.Windows.Impl.cpp"
	)
	target_sources(PonyEngine.Surface.Main PRIVATE FILE_SET CXX_MODULES FILES 
		"Source/Private/Surface.Main/Windows/Surface.Main.Windows.cppm"
		"Source/Private/Surface.Main/Windows/Surface.Main.Windows-MessageHandler.cppm"
		"Source/Private/Surface.Main/Windows/Surface.Main.Windows-SurfaceService.cppm"
		"Source/Private/Surface.Main/Windows/Surface.Main.Windows-SurfaceServiceModule.cppm"
		"Source/Private/Surface.Main/Windows/Surface.Main.Windows-WindowClass.cppm"
	)
endif()

message(VERBOSE "Configuring defines")
target_compile_definitions(PonyEngine.Surface.Main PUBLIC
	PONY_ENGINE_SURFACE_MAIN_ORDER=${PONY_ENGINE_SURFACE_MAIN_ORDER}
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Surface.Main PROPERTIES 
	CXX_STANDARD 23
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Surface.Main PUBLIC
	PonyEngine.Core
	PonyEngine.Surface
)
