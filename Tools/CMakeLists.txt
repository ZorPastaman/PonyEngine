message(STATUS "Configuring tools")

message(VERBOSE "Configuring environment")
include(FetchContent)

message(STATUS "Fetching TOML++")
FetchContent_Declare(
	tomlplusplus
	GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
	GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(tomlplusplus)

option(PONY_TOOLS_FILE_RESOURCE_MANIFEST_COMPILER "Enable PonyTools.FileResourceManifestCompiler module" ON)
option(PONY_TOOLS_FILE_RESOURCE_MANIFEST_GENERATOR "Enable PonyTools.FileResourceManifestGenerator module" ON)
option(PONY_TOOLS_PACK_RESOURCE_MANIFEST_COMPILER "Enable PonyTools.PackResourceManifestCompiler module" ON)

if(PONY_TOOLS_FILE_RESOURCE_MANIFEST_COMPILER)
	add_subdirectory("FileResourceManifestCompiler")
endif()
if(PONY_TOOLS_FILE_RESOURCE_MANIFEST_GENERATOR)
	add_subdirectory("FileResourceManifestGenerator")
endif()

if(PONY_TOOLS_PACK_RESOURCE_MANIFEST_COMPILER)
	add_subdirectory("PackResourceManifestCompiler")
endif()
