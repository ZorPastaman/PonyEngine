message(STATUS "Configuring PonyTools.WorldDataSerializer")

add_library(PonyTools.WorldDataSerializer MODULE)

target_sources(PonyTools.WorldDataSerializer PRIVATE
	"Source/Main.cpp"
 )

target_sources(PonyTools.WorldDataSerializer PRIVATE FILE_SET CXX_MODULES FILES
)

target_compile_definitions(PonyTools.WorldDataSerializer PRIVATE
	PONY_ENGINE_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
	PONY_ENGINE_VERSION_MINOR=${PROJECT_VERSION_MINOR}
	PONY_ENGINE_VERSION_PATCH=${PROJECT_VERSION_PATCH}
	PONY_ENGINE_VERSION_TWEAK=${PROJECT_VERSION_TWEAK}
)

set_target_properties(PonyTools.WorldDataSerializer PROPERTIES
	OUTPUT_NAME "PonyWorldDataSerializer"
)

target_link_libraries(PonyTools.WorldDataSerializer PRIVATE
	PonyTools.Utility
	PonyEngine.Core
	PonyEngine.World.Meta
	tomlplusplus::tomlplusplus
)
