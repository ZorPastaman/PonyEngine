message(STATUS "Configuring PonyTools.FileResourceManifestCompiler")

add_executable(PonyTools.FileResourceManifestCompiler)

target_sources(PonyTools.FileResourceManifestCompiler PRIVATE
	"Source/Main.cpp"
)

target_compile_definitions(PonyTools.FileResourceManifestCompiler PRIVATE
	PONY_ENGINE_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
	PONY_ENGINE_VERSION_MINOR=${PROJECT_VERSION_MINOR}
	PONY_ENGINE_VERSION_PATCH=${PROJECT_VERSION_PATCH}
	PONY_ENGINE_VERSION_TWEAK=${PROJECT_VERSION_TWEAK}
)

set_target_properties(PonyTools.FileResourceManifestCompiler PROPERTIES
	OUTPUT_NAME "ponyfrmc"
)

target_link_libraries(PonyTools.FileResourceManifestCompiler PRIVATE
	tomlplusplus::tomlplusplus
)
