message(STATUS "Configuring PonyTools.ResourcePacker")

add_executable(PonyTools.ResourcePacker)

target_sources(PonyTools.ResourcePacker PRIVATE
	"Source/Main.cpp"
)

target_sources(PonyTools.ResourcePacker PRIVATE FILE_SET CXX_MODULES FILES
	"Source/Manifest.cppm"
)

target_compile_definitions(PonyTools.ResourcePacker PRIVATE
	PONY_ENGINE_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
	PONY_ENGINE_VERSION_MINOR=${PROJECT_VERSION_MINOR}
	PONY_ENGINE_VERSION_PATCH=${PROJECT_VERSION_PATCH}
	PONY_ENGINE_VERSION_TWEAK=${PROJECT_VERSION_TWEAK}
)

set_target_properties(PonyTools.ResourcePacker PROPERTIES
	OUTPUT_NAME "PonyResourcePacker"
)

target_link_libraries(PonyTools.ResourcePacker PRIVATE
	PonyTools.Utility
	tomlplusplus::tomlplusplus
)
