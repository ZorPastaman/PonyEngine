macro(pony_manage_target target install_targets)
	if(TARGET ${target})
		pony_set_build_options(${target} ${PONY_ENGINE_OPTIMIZATION})
		list(APPEND ${install_targets} ${target})
	endif()
endmacro()

set(PONY_INSTALL_TARGETS "")

pony_manage_target(PonyTools.FileResourceManifestCompiler PONY_INSTALL_TARGETS)
pony_manage_target(PonyTools.FileResourceManifestGenerator PONY_INSTALL_TARGETS)

pony_manage_target(PonyTools.PackResourceManifestCompiler PONY_INSTALL_TARGETS)
pony_manage_target(PonyTools.PackResourceManifestGenerator PONY_INSTALL_TARGETS)

message(VERBOSE "Installing")
install(TARGETS ${PONY_INSTALL_TARGETS}
	RUNTIME DESTINATION .
	LIBRARY DESTINATION
)
if(PONY_TOOLS_INSTALL_DIR)
	install(TARGETS ${PONY_INSTALL_TARGETS}
		RUNTIME DESTINATION ${PONY_TOOLS_INSTALL_DIR}
		LIBRARY DESTINATION
	)
endif()
