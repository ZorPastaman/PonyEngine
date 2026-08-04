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

add_subdirectory("FileResourceManifestCompiler")
add_subdirectory("FileResourceManifestGenerator")

add_subdirectory("PackResourceManifestCompiler")
add_subdirectory("PackResourceManifestGenerator")

set(PONY_INSTALL_TARGETS "")
list(APPEND PONY_INSTALL_TARGETS PonyTools.FileResourceManifestCompiler)
list(APPEND PONY_INSTALL_TARGETS PonyTools.FileResourceManifestGenerator)
list(APPEND PONY_INSTALL_TARGETS PonyTools.PackResourceManifestCompiler)
list(APPEND PONY_INSTALL_TARGETS PonyTools.PackResourceManifestGenerator)

if(PONY_TOOLS_INSTALL_DEFAULT)
	install(TARGETS ${PONY_INSTALL_TARGETS}
		RUNTIME DESTINATION .
		LIBRARY DESTINATION
	)
endif()
if(PONY_TOOLS_INSTALL_DIR)
	install(TARGETS ${PONY_INSTALL_TARGETS}
		RUNTIME DESTINATION ${PONY_TOOLS_INSTALL_DIR}
		LIBRARY DESTINATION
	)
endif()
