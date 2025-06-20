# Set module.
if(PONY_ENGINE_FORCE_STATIC)
	add_library(GameSample STATIC)
else()
	add_library(GameSample SHARED)
endif()

target_include_directories(GameSample PUBLIC
	"Include/Public"
)
target_sources(GameSample PUBLIC
	"Source/Main.Game.cpp"
)
target_sources(GameSample PRIVATE
	"Source/Main.Game.Impl.cpp"
)
target_sources(GameSample PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Private/Game/Game.cppm"
)

set_target_properties(GameSample PROPERTIES CXX_STANDARD 23)

# Set PONY_DLL if the game is built as a shared library.
if(NOT PONY_FORCE_STATIC)
	target_compile_definitions(GameSample PRIVATE PONY_DLL)
endif()

# Set PonyEngine dependencies.
target_link_libraries(GameSample PRIVATE PonyEngine.Core)

# Add Game module to PonyEngine.
target_link_libraries(PonyEngine.Application PRIVATE GameSample)
