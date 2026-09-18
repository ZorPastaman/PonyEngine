# Packs resources to a pack.
# The resources must be in ResourceContainer format.
# data_params - path to a data parameters file.
# data_output - path to a data output file.
# manifest - manifest sub-command. Must be generated with pony_add_pack_manifest().
# DEP_FILE <path> - sets a path to a dep file. If not set, ${data_output}.d is used.
# VERBOSE - verbose flag.
# ADDITIONAL_DEPENDENCIES <dependencies> - adds additional dependencies to the command.
function(pony_pack_resources data_params data_output manifest)
	set(options VERBOSE)
	set(oneValueArgs DEP_FILE)
	set(multiValueArgs ADDITIONAL_DEPENDENCIES)
	cmake_parse_arguments(arg "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

	set(PACKER_OPTIONS -p "${data_params}" -o "${data_output}" --size_t-size ${PONY_SIZEOF_SIZE_T})
	if(PONY_IS_BIG_ENDIAN)
		list(APPEND PACKER_OPTIONS --big-endian)
	endif()
	set(PACKER_DEPENDS "${data_params}")
	set(PACKER_OUTPUT "${data_output}")

	list(LENGTH manifest manifest_count)
	set(i 0)
	while(i LESS manifest_count)
		if(i GREATER_EQUAL manifest_count)
			message(FATAL_ERROR "Invalid manifest")
		endif()
		list(GET manifest ${i} manifest_resource_list)
		math(EXPR i "${i} + 1")

		if(i GREATER_EQUAL manifest_count)
			message(FATAL_ERROR "Invalid manifest")
		endif()
		list(GET manifest ${i} manifest_params)
		math(EXPR i "${i} + 1")

		if(i GREATER_EQUAL manifest_count)
			message(FATAL_ERROR "Invalid manifest")
		endif()
		list(GET manifest ${i} manifest_output)
		math(EXPR i "${i} + 1")

		list(APPEND PACKER_OPTIONS -m "${manifest_resource_list}" "${manifest_params}" "${manifest_output}")
		list(APPEND PACKER_DEPENDS "${manifest_resource_list}" "${manifest_params}")
		list(APPEND PACKER_OUTPUT "${manifest_output}")
	endwhile()

	if(arg_VERBOSE)
		list(APPEND PACKER_OPTIONS "--verbose")
	endif()

	if(arg_DEP_FILE)
		set(PACKER_DEP_FILE_PATH "${arg_DEP_FILE}")
	else()
		set(PACKER_DEP_FILE_PATH "${data_output}.d")
	endif()
	list(APPEND PACKER_OPTIONS -d "${PACKER_DEP_FILE_PATH}")

	add_custom_command(COMMAND PonyResourcePacker ${PACKER_OPTIONS}
		DEPENDS ${PACKER_DEPENDS} ${arg_ADDITIONAL_DEPENDENCIES}
		OUTPUT ${PACKER_OUTPUT}
		DEPFILE ${PACKER_DEP_FILE_PATH}
		COMMENT "Packing resources to '${data_output}' with PonyResourcePacker"
		VERBATIM COMMAND_EXPAND_LISTS
	)
endfunction()

# Adds manifest info to the manifest_list in the correct format.
# resource_list - resource list
# manifest_params - manifest parameters file path.
# manifest_output - manifest output file path.
# manifest_list - result variable name.
macro(pony_add_pack_manifest resource_list manifest_params manifest_output manifest_list)
	list(APPEND ${manifest_list} "${resource_list}" "${manifest_params}" "${manifest_output}")
endmacro()
