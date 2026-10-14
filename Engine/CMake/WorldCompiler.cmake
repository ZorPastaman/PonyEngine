function(pony_compiler_world_definition asset data_output)
	set(options NO_DEFAULT_SERIALIZER VERBOSE)
	set(oneValueArgs DEP_FILE)
	set(multiValueArgs SERIALIZERS ADDITIONAL_DEPENDENCIES)
	cmake_parse_arguments(arg "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

	set(COMPILER_OPTIONS "${asset}" -o "${data_output}" --size_t-size ${PONY_SIZEOF_SIZE_T})
	if(PONY_IS_BIG_ENDIAN)
		list(APPEND COMPILER_OPTIONS --big-endian)
	endif()
	set(COMPILER_DEPENDS "${asset}")
	set(COMPILER_OUTPUT "${data_output}")

	if(NOT arg_NO_DEFAULT_SERIALIZER)
		list(APPEND COMPILER_OPTIONS -s "PonyWorldDataSerializer${CMAKE_SHARED_LIBRARY_SUFFIX}")
	endif()

	list(LENGTH arg_SERIALIZERS serializer_count)
	set(i 0)
	while(i LESS serializer_count)
		list(GET arg_SERIALIZERS ${i} serializer)
		list(APPEND COMPILER_OPTIONS -s "${serializer}${CMAKE_SHARED_LIBRARY_SUFFIX}")
		math(EXPR i "${i} + 1")
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

	add_custom_command(COMMAND PonyWorldDefinitionCompiler ${COMPILER_OPTIONS}
		DEPENDS ${COMPILER_DEPENDS} ${arg_ADDITIONAL_DEPENDENCIES}
		OUTPUT ${COMPILER_OUTPUT}
		DEPFILE ${COMPILER_DEP_FILE_PATH}
		COMMENT "Compiling '${asset}' to '${data_output}' with PonyWorldDefinitionCompiler"
		VERBATIM COMMAND_EXPAND_LISTS
	)
endfunction()
