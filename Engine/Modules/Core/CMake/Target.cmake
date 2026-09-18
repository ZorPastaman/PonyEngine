# Makes a shared library consisting of engine modules. It adds PONY_DLL define to each module.
# group_target - target name for the module group.
# MODULES - list of engine modules.
# GROUP_NAME - output name for the module group. By default it will have a name of the group_target.
function(pony_make_module_group group_target)
	set(oneValueArgs GROUP_NAME)
	set(multiValueArgs MODULES)
	cmake_parse_arguments(module_arg "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

	message(STATUS "Making module group: '${group_target}'. Modules: '${module_arg_MODULES}'")

	foreach(MODULE IN LISTS module_arg_MODULES)
		target_compile_definitions(${MODULE} PRIVATE PONY_DLL)
	endforeach()

	add_library(${group_target} SHARED)

	if(module_arg_GROUP_NAME)
		set_target_properties(${group_target} PROPERTIES OUTPUT_NAME "${module_arg_GROUP_NAME}")
	endif()

	target_link_libraries(${group_target} PUBLIC ${module_arg_MODULES})
endfunction()
