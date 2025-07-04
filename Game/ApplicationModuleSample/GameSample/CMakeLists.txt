# Set module.
add_library(GameSample STATIC)

# Set includes and sources.
target_include_directories(GameSample PUBLIC
	"Include/Public"
)
target_sources(GameSample PUBLIC
	"Source/Main.cpp"
)
target_sources(GameSample PRIVATE
	"Source/Main.Impl.cpp"
)
target_sources(GameSample PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Private/Game/Game.cppm"
)

# Set properties. CXX_STANDARD must be at least 23. POSITION_INDEPENDENT_CODE TRUE is required to build a shared library groups consisting of this static lib.
set_target_properties(GameSample PROPERTIES 
	CXX_STANDARD 23
	POSITION_INDEPENDENT_CODE TRUE
)

# Set PonyEngine dependencies.
target_link_libraries(GameSample PUBLIC 
	PonyEngine.Core
)
