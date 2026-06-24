# Makes a shared library consisting of engine modules. It adds PONY_DLL define to each module.
# group_target - target name for the module group.
# MODULES - list of engine modules.
# GROUP_NAME - output name for the module group. By default it will have a name of the group_target.
# CXX_STANDARD - C++ standard. By default, C++ 23.
function(pony_make_module_group group_target)
	set(oneValueArgs GROUP_NAME CXX_STANDARD)
	set(multiValueArgs MODULES)
	cmake_parse_arguments(module_arg "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

	message(STATUS "Making module group: ${group_target}. Modules: ${module_arg_MODULES}")

	message(VERBOSE "Adding PONY_DLL define")
	foreach(MODULE IN LISTS module_arg_MODULES)
		target_compile_definitions(${MODULE} PRIVATE PONY_DLL)
	endforeach()

	message(VERBOSE "Configuring target")
	add_library(${group_target} SHARED)

	if(NOT module_arg_CXX_STANDARD)
		set(module_arg_CXX_STANDARD 23)
	endif()

	message(VERBOSE "Setting properties")
	set_target_properties(${group_target} PROPERTIES 
		CXX_STANDARD ${module_arg_CXX_STANDARD}
		CXX_STANDARD_REQUIRED ON
		POSITION_INDEPENDENT_CODE TRUE
	)
	if(module_arg_GROUP_NAME)
		set_target_properties(${group_target} PROPERTIES OUTPUT_NAME ${module_arg_GROUP_NAME})
	endif()

	message(VERBOSE "Configuring dependencies")
	target_link_libraries(${group_target} PUBLIC ${module_arg_MODULES})
endfunction()
