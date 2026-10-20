message(STATUS "Configuring PonyTools.WorldDefinitionCompiler")

add_executable(PonyTools.WorldDefinitionCompiler)

target_sources(PonyTools.WorldDefinitionCompiler PRIVATE
	"Source/Main.cpp"
)

target_sources(PonyTools.WorldDefinitionCompiler PRIVATE FILE_SET CXX_MODULES FILES
	"Source/World.cppm"
)

target_compile_definitions(PonyTools.WorldDefinitionCompiler PRIVATE
	PONY_ENGINE_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
	PONY_ENGINE_VERSION_MINOR=${PROJECT_VERSION_MINOR}
	PONY_ENGINE_VERSION_PATCH=${PROJECT_VERSION_PATCH}
	PONY_ENGINE_VERSION_TWEAK=${PROJECT_VERSION_TWEAK}
)

set_target_properties(PonyTools.WorldDefinitionCompiler PROPERTIES
	OUTPUT_NAME "PonyWorldDefinitionCompiler"
)

target_link_libraries(PonyTools.WorldDefinitionCompiler PRIVATE
	PonyTools.Utility
	PonyEngine.Core
	tomlplusplus::tomlplusplus
)
