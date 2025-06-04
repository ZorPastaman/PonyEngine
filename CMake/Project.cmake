# Sets global properties with install folders.
function(pony_init_install)
	set_property(GLOBAL PROPERTY PONY_APP_INSTALL_PATH .)
endfunction()

# Adds an application module.
# target_name Application module to add.
function(pony_add_app_module target_name)
	set_property(GLOBAL APPEND PROPERTY PONY_APP_MODULES ${target_name})
endfunction()

# Links application modules.
# target_name Application target.
function(pony_link_app_modules target_name)
	get_property(PONY_APP_MODULES_VALUE GLOBAL PROPERTY PONY_APP_MODULES)
	message(STATUS "Linking application modules: ${PONY_APP_MODULES_VALUE}")
	target_link_libraries(${target_name} PRIVATE ${PONY_APP_MODULES_VALUE})
endfunction()
