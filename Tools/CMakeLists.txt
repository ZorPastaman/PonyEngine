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

if(PONY_TOOLS_FILE_RESOURCE_MANIFEST_COMPILER)
	add_subdirectory("FileResourceManifestCompiler")
endif()
