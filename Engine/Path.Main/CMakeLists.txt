message(STATUS "Configuring PonyEngine.Path.Main")

message(VERBOSE "Validating settings")
if(NOT TARGET PonyEngine.Path)
	message(FATAL_ERROR "PonyEngine.Path wasn't configured")
endif()
if(NOT TARGET PonyEngine.Path.Extension)
	message(FATAL_ERROR "PonyEngine.Path.Extension wasn't configured")
endif()

if(NOT PONY_ENGINE_PATH_MAIN_ORDER)
	message(FATAL_ERROR "PONY_ENGINE_PATH_MAIN is set but PONY_ENGINE_PATH_MAIN_ORDER isn't")
endif()
string(SUBSTRING "${PONY_ENGINE_PATH_MAIN_ORDER}" 0 1 ORDER_FIRST_CHAR)
if(NOT ORDER_FIRST_CHAR MATCHES "^[b-y]$")
	message(FATAL_ERROR "PONY_ENGINE_PATH_MAIN_ORDER is incorrect. Its first letter must be inside b-y range")
endif()

message(VERBOSE "Configuring target")
add_library(PonyEngine.Path.Main STATIC)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Path.Main PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Private/Path.Main/Path.Main.cppm"
	"Source/Private/Path.Main/Path.Main-PathService.cppm"
	"Source/Private/Path.Main/Path.Main-PathServiceFactory.cppm"
)

if(PONY_WINDOWS)
	message(VERBOSE "Configuring headers for Windows")
	target_include_directories(PonyEngine.Path.Main PUBLIC
		"Include/Public/Windows"
	)

	message(VERBOSE "Configuring sources for Windows")
	target_sources(PonyEngine.Path.Main PUBLIC
		"Source/Main.Windows.cpp"
	)
	target_sources(PonyEngine.Path.Main PRIVATE
		"Source/Main.Windows.Impl.cpp"
	)
	target_sources(PonyEngine.Path.Main PRIVATE FILE_SET CXX_MODULES FILES 
		"Source/Private/Path.Main/Windows/Path.Main.Windows.cppm"
		"Source/Private/Path.Main/Windows/Path.Main.Windows-PathServiceFactory.cppm"
		"Source/Private/Path.Main/Windows/Path.Main.Windows-PathServiceModule.cppm"
	)
endif()

message(VERBOSE "Configuring defines")
target_compile_definitions(PonyEngine.Path.Main PUBLIC
	PONY_ENGINE_PATH_MAIN_ORDER=${PONY_ENGINE_PATH_MAIN_ORDER}
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Path.Main PROPERTIES 
	CXX_STANDARD 23
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Path.Main PUBLIC
	PonyEngine.Core
	PonyEngine.Path
	PonyEngine.Path.Extension
)
