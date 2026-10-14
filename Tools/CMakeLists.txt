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

set(PONY_ENGINE_CORE ON)
set(PONY_ENGINE_WORLD ON)
set(PONY_ENGINE_WORLD_HIERARCHY ON)
add_subdirectory("../Engine/Modules" "${CMAKE_CURRENT_BINARY_DIR}/Engine/Modules")

add_subdirectory("Utility")

add_subdirectory("TextCompiler")
add_subdirectory("WorldDefinitionCompiler")
add_subdirectory("WorldDataSerializer")
add_subdirectory("ResourcePacker")

set(PONY_INSTALL_TARGETS "")
list(APPEND PONY_INSTALL_TARGETS PonyTools.TextCompiler)
list(APPEND PONY_INSTALL_TARGETS PonyTools.WorldDefinitionCompiler)
list(APPEND PONY_INSTALL_TARGETS PonyTools.WorldDataSerializer)
list(APPEND PONY_INSTALL_TARGETS PonyTools.ResourcePacker)

set(PONY_TOOLS_INSTALL_DIR "." CACHE STRING "Install directory for Pony Tools.")

install(TARGETS ${PONY_INSTALL_TARGETS}
	RUNTIME DESTINATION ${PONY_TOOLS_INSTALL_DIR}
	LIBRARY DESTINATION ${PONY_TOOLS_INSTALL_DIR}
)
