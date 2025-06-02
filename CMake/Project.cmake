# Initializes project global properties.
function(pony_init_project)
	set_property(GLOBAL PROPERTY PONY_APP_MODULES)
	set_property(GLOBAL PROPERTY PONY_INSTALL)
endfunction()

# Adds an application module.
# target_name Application module to add.
function(pony_add_app_module target_name)
	set_property(GLOBAL APPEND PROPERTY PONY_APP_MODULES ${target_name})
endfunction()

# Links application modules.
# target_name Application target.
function(pony_target_link_app_modules target_name)
	get_property(PONY_APP_MODULES_VALUE GLOBAL PROPERTY PONY_APP_MODULES)
	target_link_libraries(${target_name} PRIVATE ${PONY_APP_MODULES_VALUE})
endfunction()

# Adds a target to install.
# target_name Target to install.
function(pony_add_install target_name)
	set_property(GLOBAL APPEND PROPERTY PONY_INSTALL ${target_name})
endfunction()

# Installs all added targets.
function(pony_install)
	get_property(PONY_INSTALL_VALUE GLOBAL PROPERTY PONY_INSTALL)
	install(TARGETS ${PONY_INSTALL_VALUE} RUNTIME DESTINATION .)
endfunction()
