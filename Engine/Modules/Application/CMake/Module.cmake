# Validates the module order.
# module_order - Module order variable.
function(pony_validate_module_order module_order)
	if(NOT DEFINED ${module_order} OR ${module_order} STREQUAL "")
		message(FATAL_ERROR "'${module_order}' isn't set")
	endif()

	string(SUBSTRING ${${module_order}} 0 1 ORDER_FIRST_CHAR)
	if(NOT ORDER_FIRST_CHAR MATCHES "^[b-y]$")
		message(FATAL_ERROR "'${module_order}' is incorrect. Its first letter must be inside b-y range")
	endif()	
endfunction()

# Validates the tick order.
# tick_order - Tick order variable.
function(pony_validate_tick_order tick_order)
	if(NOT DEFINED ${tick_order} OR ${tick_order} STREQUAL "")
		message(FATAL_ERROR "'${tick_order}' isn't set")
	endif()

	if(NOT ${${tick_order}} MATCHES "^[+-]?[0-9]+$")
		message(FATAL_ERROR "'${tick_order}' is incorrect. It must be an int32 number")
	endif()

	if(${${tick_order}} LESS -2147483648 OR ${${tick_order}} GREATER 2147483647)
		message(FATAL_ERROR "'${tick_order}' is incorrect. It must be an int32 number")
	endif()
endfunction()

# Makes a shared library consisting of engine modules. It adds PONY_MODULE_DLL define to each module.
# group_target - target name for the module group.
# MODULES - list of engine modules.
# GROUP_NAME - output name for the module group. By default it will have a name of the group_target.
function(pony_make_module_group group_target)
	set(oneValueArgs GROUP_NAME)
	set(multiValueArgs MODULES)
	cmake_parse_arguments(module_arg "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

	message(STATUS "Making module group: '${group_target}'. Modules: '${module_arg_MODULES}'")

	foreach(MODULE IN LISTS module_arg_MODULES)
		target_compile_definitions(${MODULE} PRIVATE PONY_MODULE_DLL)
	endforeach()

	add_library(${group_target} SHARED)

	if(module_arg_GROUP_NAME)
		set_target_properties(${group_target} PROPERTIES OUTPUT_NAME "${module_arg_GROUP_NAME}")
	endif()

	target_link_libraries(${group_target} PUBLIC ${module_arg_MODULES})
endfunction()
