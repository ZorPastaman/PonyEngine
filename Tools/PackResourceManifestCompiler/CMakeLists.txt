message(STATUS "Configuring PonyTools.PackResourceManifestCompiler")

message(VERBOSE "Configuring target")
add_executable(PonyTools.PackResourceManifestCompiler)

message(VERBOSE "Configuring sources")
target_sources(PonyTools.PackResourceManifestCompiler PRIVATE
	"Source/Main.cpp"
)

message(VERBOSE "Configuring defines")
target_compile_definitions(PonyTools.PackResourceManifestCompiler PRIVATE
	PONY_ENGINE_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
	PONY_ENGINE_VERSION_MINOR=${PROJECT_VERSION_MINOR}
	PONY_ENGINE_VERSION_PATCH=${PROJECT_VERSION_PATCH}
	PONY_ENGINE_VERSION_TWEAK=${PROJECT_VERSION_TWEAK}
)

message(VERBOSE "Setting properties")
set_target_properties(PonyTools.PackResourceManifestCompiler PROPERTIES
	OUTPUT_NAME "ponyprmc"
)

message(VERBOSE "Configuring dependencies")
target_link_libraries(PonyTools.PackResourceManifestCompiler PRIVATE
	tomlplusplus::tomlplusplus
)
