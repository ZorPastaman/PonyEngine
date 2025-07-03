message(STATUS "Configuring PonyEngine.Engine.Main")

message(VERBOSE "Validating settings")

if(NOT TARGET PonyEngine.Engine.Extension)
	message(FATAL_ERROR "PonyEngine.Engine.Extension wasn't configured")
endif()

message(VERBOSE "Configuring target")
add_library(PonyEngine.Engine.Main STATIC)

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.Engine.Main PUBLIC
	"Include/Public"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Engine.Main PUBLIC
	"Source/Main.cpp"
)
target_sources(PonyEngine.Engine.Main PRIVATE
	"Source/Main.Impl.cpp"
)
target_sources(PonyEngine.Engine.Main PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Private/Engine.Main/Engine.Main.cppm"
	"Source/Private/Engine.Main/Engine.Main-Engine.cppm"
	"Source/Private/Engine.Main/Engine.Main-EngineFactory.cppm"
	"Source/Private/Engine.Main/Engine.Main-EngineLogger.cppm"
	"Source/Private/Engine.Main/Engine.Main-EngineModule.cppm"
	"Source/Private/Engine.Main/Engine.Main-ExitCodes.cppm"
	"Source/Private/Engine.Main/Engine.Main-SystemManager.cppm"
)

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Engine.Main PROPERTIES 
	CXX_STANDARD 23
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Engine.Main PRIVATE
	PonyEngine.Core
	PonyEngine.Engine.Extension
)
