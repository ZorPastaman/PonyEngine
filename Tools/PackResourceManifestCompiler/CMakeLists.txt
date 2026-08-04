message(STATUS "Configuring PonyTools.PackResourceManifestCompiler")

add_executable(PonyTools.PackResourceManifestCompiler)

target_sources(PonyTools.PackResourceManifestCompiler PRIVATE
	"Source/Main.cpp"
)

target_compile_definitions(PonyTools.PackResourceManifestCompiler PRIVATE
	PONY_ENGINE_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
	PONY_ENGINE_VERSION_MINOR=${PROJECT_VERSION_MINOR}
	PONY_ENGINE_VERSION_PATCH=${PROJECT_VERSION_PATCH}
	PONY_ENGINE_VERSION_TWEAK=${PROJECT_VERSION_TWEAK}
)

set_target_properties(PonyTools.PackResourceManifestCompiler PROPERTIES
	OUTPUT_NAME "ponyprmc"
)

target_link_libraries(PonyTools.PackResourceManifestCompiler PRIVATE
	tomlplusplus::tomlplusplus
)
