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

add_subdirectory("FileResourceManifestCompiler")
add_subdirectory("FileResourceManifestGenerator")

add_subdirectory("PackResourceManifestCompiler")
