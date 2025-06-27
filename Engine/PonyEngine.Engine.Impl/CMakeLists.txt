message(STATUS "Configuring PonyEngine.Engine.Impl")

message(VERBOSE "Validating settings")

if(NOT TARGET PonyEngine.Engine.Ext)
	message(FATAL_ERROR "PonyEngine.Engine.Ext wasn't configured")
endif()

if(PONY_ENGINE_FORCE_STATIC)
	message(VERBOSE "Configuring target as static")
	add_library(PonyEngine.Engine.Impl STATIC)
else()
	message(VERBOSE "Configuring target as shared")
	add_library(PonyEngine.Engine.Impl SHARED)
endif()

message(VERBOSE "Configuring headers")
target_include_directories(PonyEngine.Engine.Impl PUBLIC
	"Include/Public"
)

message(VERBOSE "Configuring sources")
target_sources(PonyEngine.Engine.Impl PUBLIC
	"Source/Main.Engine.cpp"
)
target_sources(PonyEngine.Engine.Impl PRIVATE
	"Source/Main.Engine.Impl.cpp"
)
target_sources(PonyEngine.Engine.Impl PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Private/Engine.Core/Engine.Core.cppm"
	"Source/Private/Engine.Core/Engine.Core-Engine.cppm"
	"Source/Private/Engine.Core/Engine.Core-EngineFactory.cppm"
	"Source/Private/Engine.Core/Engine.Core-EngineLogger.cppm"
	"Source/Private/Engine.Core/Engine.Core-EngineModule.cppm"
	"Source/Private/Engine.Core/Engine.Core-ExitCodes.cppm"
	"Source/Private/Engine.Core/Engine.Core-SystemManager.cppm"
)

message(VERBOSE "Configuring defines")
if(NOT PONY_FORCE_STATIC)
	target_compile_definitions(PonyEngine.Engine.Impl PRIVATE PONY_DLL)
endif()

message(VERBOSE "Setting properties")
set_target_properties(PonyEngine.Engine.Impl PROPERTIES 
	CXX_STANDARD 23
	OUTPUT_NAME "PonyEngine.Engine"
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyEngine.Engine.Impl PRIVATE
	PonyEngine.Core
	PonyEngine.Engine.Ext
)
