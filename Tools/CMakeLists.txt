message(STATUS "Configuring tools")

include(FetchContent)

message(STATUS "Fetching TOML++")
FetchContent_Declare(
	tomlplusplus
	GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
	GIT_TAG v3.4.0
	GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(tomlplusplus)

add_subdirectory("Utility")

add_subdirectory("TextCompiler")
add_subdirectory("ResourcePacker")

set(PONY_INSTALL_TARGETS "")
list(APPEND PONY_INSTALL_TARGETS PonyTools.TextCompiler)
list(APPEND PONY_INSTALL_TARGETS PonyTools.ResourcePacker)

install(TARGETS ${PONY_INSTALL_TARGETS}
	RUNTIME DESTINATION .
	LIBRARY DESTINATION
)
