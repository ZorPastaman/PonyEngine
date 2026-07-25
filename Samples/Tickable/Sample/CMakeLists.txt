# Set module.
add_library(Sample STATIC)

# Set includes and sources.
target_include_directories(Sample PUBLIC
	"Include/Public"
)
target_sources(Sample PUBLIC
	"Source/Launch.cpp"
)
target_sources(Sample PRIVATE
	"Source/Launch.Impl.cpp"
)
target_sources(Sample PRIVATE FILE_SET CXX_MODULES FILES 
	"Source/Game.cppm"
	"Source/Game-GameService.cppm"
	"Source/Game-GameServiceModule.cppm"
)

# Set properties. CXX_STANDARD must be at least 23. POSITION_INDEPENDENT_CODE TRUE is required to build shared library groups consisting of this static lib.
set_target_properties(Sample PROPERTIES 
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE TRUE
)

# Set dependencies.
target_link_libraries(Sample PUBLIC 
	PonyEngine.Application
)
target_link_libraries(Sample PRIVATE
	PonyEngine.Core
	PonyEngine.Job
	PonyEngine.Log
)
