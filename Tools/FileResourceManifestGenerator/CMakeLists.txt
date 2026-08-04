message(STATUS "Configuring PonyTools.FileResourceManifestGenerator")

add_executable(PonyTools.FileResourceManifestGenerator)

target_sources(PonyTools.FileResourceManifestGenerator PRIVATE
	"Source/Main.cpp"
)

target_compile_definitions(PonyTools.FileResourceManifestGenerator PRIVATE
	PONY_ENGINE_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
	PONY_ENGINE_VERSION_MINOR=${PROJECT_VERSION_MINOR}
	PONY_ENGINE_VERSION_PATCH=${PROJECT_VERSION_PATCH}
	PONY_ENGINE_VERSION_TWEAK=${PROJECT_VERSION_TWEAK}
)

set_target_properties(PonyTools.FileResourceManifestGenerator PROPERTIES
	OUTPUT_NAME "ponyfrmg"
)

target_link_libraries(PonyTools.FileResourceManifestGenerator PRIVATE
	tomlplusplus::tomlplusplus
)
