message(STATUS "Configuring PonyTools.PackResourceManifestGenerator")

add_executable(PonyTools.PackResourceManifestGenerator)

target_sources(PonyTools.PackResourceManifestGenerator PRIVATE
	"Source/Main.cpp"
)

target_compile_definitions(PonyTools.PackResourceManifestGenerator PRIVATE
	PONY_ENGINE_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
	PONY_ENGINE_VERSION_MINOR=${PROJECT_VERSION_MINOR}
	PONY_ENGINE_VERSION_PATCH=${PROJECT_VERSION_PATCH}
	PONY_ENGINE_VERSION_TWEAK=${PROJECT_VERSION_TWEAK}
)

set_target_properties(PonyTools.PackResourceManifestGenerator PROPERTIES
	OUTPUT_NAME "ponyprmg"
)

target_link_libraries(PonyTools.PackResourceManifestGenerator PRIVATE
	tomlplusplus::tomlplusplus
)
