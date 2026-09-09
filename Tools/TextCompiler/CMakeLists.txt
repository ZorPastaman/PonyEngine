message(STATUS "Configuring PonyTools.TextCompiler")

add_executable(PonyTools.TextCompiler)

target_sources(PonyTools.TextCompiler PRIVATE
	"Source/Main.cpp"
)

target_compile_definitions(PonyTools.TextCompiler PRIVATE
	PONY_ENGINE_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
	PONY_ENGINE_VERSION_MINOR=${PROJECT_VERSION_MINOR}
	PONY_ENGINE_VERSION_PATCH=${PROJECT_VERSION_PATCH}
	PONY_ENGINE_VERSION_TWEAK=${PROJECT_VERSION_TWEAK}
)

set_target_properties(PonyTools.TextCompiler PROPERTIES
	OUTPUT_NAME "PonyTextCompiler"
)

target_link_libraries(PonyTools.TextCompiler PRIVATE
	PonyTools.DepFile
	tomlplusplus::tomlplusplus
)
