# Set module.
add_library(GameSample STATIC)

# Set includes and sources.
target_include_directories(GameSample PUBLIC
	"Include/Public"
)
target_sources(GameSample PUBLIC
	"Source/Launch.cpp"
)
target_sources(GameSample PRIVATE
	"Source/Launch.Impl.cpp"
)
target_sources(GameSample PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Game.cppm"
	"Source/Game-GameService.cppm"
	"Source/Game-GameServiceModule.cppm"
)

# Set properties. CXX_STANDARD must be at least 23. POSITION_INDEPENDENT_CODE TRUE is required to build shared library groups consisting of this static lib.
set_target_properties(GameSample PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

# Set dependencies.
target_link_libraries(GameSample PUBLIC 
	PonyEngine.Application.Ext
)
target_link_libraries(GameSample PRIVATE
	PonyEngine.Core
	PonyEngine.Log
)
