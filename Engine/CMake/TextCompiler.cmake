# Launches PonyTextCompiler to compile a text asset.
# PonyTextCompiler must be available via the environment.
# assset - path to an asset to compile.
# data_params - path to a data parameters file.
# data_output - path to a data output file.
# load - load sub-command. Must be generated with pony_add_resource_load().
# DEP_FILE <path> - sets a path to a dep file. If not set, ${data_output}.d is used.
# VERBOSE - verbose flag.
# ADDITIONAL_DEPENDENCIES <dependencies> - adds additional dependencies to the command.
function(pony_compile_text asset data_params data_output load)
	set(options VERBOSE)
	set(oneValueArgs DEP_FILE)
	set(multiValueArgs ADDITIONAL_DEPENDENCIES)
	cmake_parse_arguments(arg "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

	set(COMPILER_OPTIONS "${asset}" -p "${data_params}" -o "${data_output}")
	set(COMPILER_DEPENDS "${asset}" "${data_params}")
	set(COMPILER_OUTPUT "${data_output}")

	list(LENGTH load load_count)
	set(i 0)
	while(i LESS load_count)
		if(i GREATER_EQUAL load_count)
			message(FATAL_ERROR "Invalid load")
		endif()
		list(GET load ${i} load_params)
		math(EXPR i "${i} + 1")

		if(i GREATER_EQUAL load_count)
			message(FATAL_ERROR "Invalid load")
		endif()
		list(GET load ${i} load_output)
		math(EXPR i "${i} + 1")

		list(APPEND COMPILER_OPTIONS -l "${load_params}" "${load_output}")
		list(APPEND COMPILER_DEPENDS "${load_params}")
		list(APPEND COMPILER_OUTPUT "${load_output}")
	endwhile()

	if(arg_VERBOSE)
		list(APPEND COMPILER_OPTIONS "--verbose")
	endif()

	if(arg_DEP_FILE)
		set(COMPILER_DEP_FILE_PATH "${arg_DEP_FILE}")
	else()
		set(COMPILER_DEP_FILE_PATH "${data_output}.d")
	endif()
	list(APPEND COMPILER_OPTIONS -d "${COMPILER_DEP_FILE_PATH}")

	add_custom_command(COMMAND PonyTextCompiler ${COMPILER_OPTIONS}
		DEPENDS ${COMPILER_DEPENDS} ${arg_ADDITIONAL_DEPENDENCIES}
		OUTPUT ${COMPILER_OUTPUT}
		DEPFILE ${COMPILER_DEP_FILE_PATH}
		COMMENT "Compiling '${asset}' to '${data_output}' with PonyTextCompiler"
		VERBATIM COMMAND_EXPAND_LISTS
	)
endfunction()
