message(STATUS "Configuring PonyEngine.Log.Main")

message(VERBOSE "Validating settings")
if(NOT TARGET PonyEngine.Log.Extension)
	message(FATAL_ERROR "PonyEngine.Log.Extension wasn't configured")
endif()

message(VERBOSE "Configuring target")
add_library(PonyEngine.Log.Main STATIC)

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.Log.Main PUBLIC
	"Include/Public"
)

if(PONY_ENGINE_LOG_CORE)
	message(VERBOSE "Configuring core sources")
	target_sources(PonyEngine.Log.Main PUBLIC
		"Source/Main.cpp"
	)
	target_sources(PonyEngine.Log.Main PRIVATE
		"Source/Main.Impl.cpp"
	)
	target_sources(PonyEngine.Log.Main PRIVATE FILE_SET CXX_MODULES FILES 
		"Source/Private/Log.Main/Log.Main.cppm"
		"Source/Private/Log.Main/Log.Main-Logger.cppm"
		"Source/Private/Log.Main/Log.Main-LoggerFactory.cppm"
		"Source/Private/Log.Main/Log.Main-LoggerModule.cppm"
	)
endif()

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Log.Main PROPERTIES 
	CXX_STANDARD 23
	POSITION_INDEPENDENT_CODE TRUE
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Log.Main PUBLIC
	PonyEngine.Core
	PonyEngine.Log.Extension
)
