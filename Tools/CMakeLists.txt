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

add_subdirectory("DepFile")

add_subdirectory("TextCompiler")

set(PONY_INSTALL_TARGETS "")
list(APPEND PONY_INSTALL_TARGETS PonyTools.TextCompiler)

install(TARGETS ${PONY_INSTALL_TARGETS}
	RUNTIME DESTINATION .
	LIBRARY DESTINATION
)
