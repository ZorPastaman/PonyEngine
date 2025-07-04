# Makes a shared library consisting of engine modules. It adds PONY_DLL define to each module.
# modules - list of engine modules.
# group_target - target name for the module group.
# group_name - output name for the module group.
# cpp_standard - C++ standard.
function(pony_make_module_group modules group_target group_name cpp_standard)
	message(STATUS "Making module group: ${group_name}. Modules: ${${modules}}")

	message(VERBOSE "Adding PONY_DLL define")
	foreach(MODULE IN LISTS ${modules})
		target_compile_definitions(${MODULE} PRIVATE PONY_DLL)
	endforeach()

	message(VERBOSE "Configuring target")
	add_library(${group_target} SHARED)

	message(VERBOSE "Setting properties")
	set_target_properties(${group_target} PROPERTIES 
		CXX_STANDARD ${cpp_standard}
		POSITION_INDEPENDENT_CODE TRUE
		OUTPUT_NAME ${group_name}
	)

	message(VERBOSE "Configuring dependencies")
	target_link_libraries(${group_target} PUBLIC
		${${modules}}
	)
endfunction()
