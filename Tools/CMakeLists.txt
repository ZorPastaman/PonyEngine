message(STATUS "Configuring tools")

message(VERBOSE "Configuring environment")
include(FetchContent)

message(STATUS "Fetching TOML++")
FetchContent_Declare(
	tomlplusplus
	GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
	GIT_TAG v3.4.0
	GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(tomlplusplus)

add_subdirectory("FileResourceManifestCompiler")
add_subdirectory("FileResourceManifestGenerator")

add_subdirectory("PackResourceManifestCompiler")
add_subdirectory("PackResourceManifestGenerator")
