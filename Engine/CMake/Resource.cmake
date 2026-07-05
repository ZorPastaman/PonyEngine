include(CheckTypeSize)

function(pony_create_file_resource_manifest path)
	set(multiValueArgs ADDITIONAL_PARAMS)
	cmake_parse_arguments(pfrmg_arg "" "" "${multiValueArgs}" ${ARGN})

	if("${PONY_TOOLS_INSTALL_DIR}" STREQUAL "")
		message(FATAL_ERROR "PONY_TOOLS_INSTALL_DIR isn't set")
	endif()

	if("${path}" STREQUAL "")
		message(FATAL_ERROR "Empty path")
	endif()

	set(PONY_FRMG "${PONY_TOOLS_INSTALL_DIR}/ponyfrmg${CMAKE_EXECUTABLE_SUFFIX}")
	if(NOT EXISTS "${PONY_FRMG}")
		message(FATAL_ERROR "'${PONY_FRMG}' not found")
	endif()

	cmake_path(ABSOLUTE_PATH path NORMALIZE OUTPUT_VARIABLE path_abs)

	set(PFRMG_OPTIONS "")

	if(pfrmg_arg_ADDITIONAL_PARAMS)
		list(APPEND PFRMG_OPTIONS ${pfrmg_arg_ADDITIONAL_PARAMS})
	endif()

	message(STATUS "Creating '${path}' with ponyfrmg")
	execute_process(COMMAND "${PONY_FRMG}" "${path_abs}" --create ${PFRMG_OPTIONS}
		COMMAND_ERROR_IS_FATAL ANY
	)
endfunction()

function(pony_add_to_file_resource_manifest path)
	set(multiValueArgs RESOURCES ADDITIONAL_PARAMS)
	cmake_parse_arguments(pfrmg_arg "" "" "${multiValueArgs}" ${ARGN})

	if("${PONY_TOOLS_INSTALL_DIR}" STREQUAL "")
		message(FATAL_ERROR "PONY_TOOLS_INSTALL_DIR isn't set")
	endif()

	if("${path}" STREQUAL "")
		message(FATAL_ERROR "Empty path")
	endif()

	set(PONY_FRMG "${PONY_TOOLS_INSTALL_DIR}/ponyfrmg${CMAKE_EXECUTABLE_SUFFIX}")
	if(NOT EXISTS "${PONY_FRMG}")
		message(FATAL_ERROR "'${PONY_FRMG}' not found")
	endif()

	if(NOT pfrmg_arg_RESOURCES)
		return()
	endif()

	cmake_path(ABSOLUTE_PATH path NORMALIZE OUTPUT_VARIABLE path_abs)

	set(ADD_LIST "")
	foreach(RESOURCE IN LISTS pfrmg_arg_RESOURCES)
		list(APPEND ADD_LIST --add "${RESOURCE}")
	endforeach()

	set(PFRMG_OPTIONS "")

	if(pfrmg_arg_ADDITIONAL_PARAMS)
		list(APPEND PFRMG_OPTIONS ${pfrmg_arg_ADDITIONAL_PARAMS})
	endif()

	message(STATUS "Adding '${pfrmg_arg_RESOURCES}' to '${path}' with ponyfrmg")
	execute_process(COMMAND "${PONY_FRMG}" "${path_abs}" ${ADD_LIST} ${PFRMG_OPTIONS}
		COMMAND_ERROR_IS_FATAL ANY
	)
endfunction()

function(pony_remove_from_file_resource_manifest path)
	set(multiValueArgs IDS ADDITIONAL_PARAMS)
	cmake_parse_arguments(pfrmg_arg "" "" "${multiValueArgs}" ${ARGN})

	if("${PONY_TOOLS_INSTALL_DIR}" STREQUAL "")
		message(FATAL_ERROR "PONY_TOOLS_INSTALL_DIR isn't set")
	endif()

	if("${path}" STREQUAL "")
		message(FATAL_ERROR "Empty path")
	endif()

	set(PONY_FRMG "${PONY_TOOLS_INSTALL_DIR}/ponyfrmg${CMAKE_EXECUTABLE_SUFFIX}")
	if(NOT EXISTS "${PONY_FRMG}")
		message(FATAL_ERROR "'${PONY_FRMG}' not found")
	endif()

	if(NOT pfrmg_arg_IDS)
		return()
	endif()

	cmake_path(ABSOLUTE_PATH path NORMALIZE OUTPUT_VARIABLE path_abs)

	set(REMOVE_LIST "")
	foreach(ID IN LISTS pfrmg_arg_IDS)
		list(APPEND REMOVE_LIST --remove "${ID}")
	endforeach()

	set(PFRMG_OPTIONS "")

	if(pfrmg_arg_ADDITIONAL_PARAMS)
		list(APPEND PFRMG_OPTIONS ${pfrmg_arg_ADDITIONAL_PARAMS})
	endif()

	message(STATUS "Removing '${pfrmg_arg_IDS}' from '${path}' with ponyfrmg")
	execute_process(COMMAND "${PONY_FRMG}" "${path_abs}" ${REMOVE_LIST} ${PFRMG_OPTIONS}
		COMMAND_ERROR_IS_FATAL ANY
	)
endfunction()

function(pony_upgrade_file_resource_manifest path)
	set(multiValueArgs ADDITIONAL_PARAMS)
	cmake_parse_arguments(pfrmg_arg "" "" "${multiValueArgs}" ${ARGN})

	if("${PONY_TOOLS_INSTALL_DIR}" STREQUAL "")
		message(FATAL_ERROR "PONY_TOOLS_INSTALL_DIR isn't set")
	endif()

	if("${path}" STREQUAL "")
		message(FATAL_ERROR "Empty path")
	endif()

	set(PONY_FRMG "${PONY_TOOLS_INSTALL_DIR}/ponyfrmg${CMAKE_EXECUTABLE_SUFFIX}")
	if(NOT EXISTS "${PONY_FRMG}")
		message(FATAL_ERROR "'${PONY_FRMG}' not found")
	endif()

	cmake_path(ABSOLUTE_PATH path NORMALIZE OUTPUT_VARIABLE path_abs)

	set(PFRMG_OPTIONS "")

	if(pfrmg_arg_ADDITIONAL_PARAMS)
		list(APPEND PFRMG_OPTIONS ${pfrmg_arg_ADDITIONAL_PARAMS})
	endif()

	message(STATUS "Upgrading '${path}' with ponyfrmg")
	execute_process(COMMAND "${PONY_FRMG}" "${path_abs}" --upgrade ${PFRMG_OPTIONS}
		COMMAND_ERROR_IS_FATAL ANY
	)
endfunction()

function(pony_make_resource_for_file_resource_manifest id type path resource)
	set(${resource} "${id},${type},${path}" PARENT_SCOPE)
endfunction()

function(pony_compile_file_resource_manifest input output)
	set(multiValueArgs ADDITIONAL_PARAMS)
	cmake_parse_arguments(pfrmc_arg "" "" "${multiValueArgs}" ${ARGN})

	if("${PONY_TOOLS_INSTALL_DIR}" STREQUAL "")
		message(FATAL_ERROR "PONY_TOOLS_INSTALL_DIR isn't set")
	endif()

	if(${input} STREQUAL "")
		message(FATAL_ERROR "Empty input")
	endif()
	if(${output} STREQUAL "")
		message(FATAL_ERROR "Empty output")
	endif()

	set(PONY_FRMC "${PONY_TOOLS_INSTALL_DIR}/ponyfrmc${CMAKE_EXECUTABLE_SUFFIX}")
	if(NOT EXISTS "${PONY_FRMC}")
		message(FATAL_ERROR "'${PONY_FRMC}' not found")
	endif()

	cmake_path(ABSOLUTE_PATH input NORMALIZE OUTPUT_VARIABLE input_abs)
	cmake_path(ABSOLUTE_PATH output NORMALIZE OUTPUT_VARIABLE output_abs)

	set(PFRMC_OPTIONS "")

	if(pfrmc_arg_ADDITIONAL_PARAMS)
		list(APPEND PFRMC_OPTIONS ${pfrmc_arg_ADDITIONAL_PARAMS})
	endif()

	add_custom_command(COMMAND "${PONY_FRMC}" "${input_abs}" -o "${output_abs}" ${PFRMC_OPTIONS}
		DEPENDS "${input_abs}"
		OUTPUT "${output_abs}"
		COMMENT "Compiling '${input}' to '${output}' with ponyfrmc"
		VERBATIM COMMAND_EXPAND_LISTS
	)
endfunction()

function(pony_compile_pack_resource_manifest input pack_output manifest_output)
	set(oneValueArgs ROOT)
	set(multiValueArgs ADDITIONAL_PARAMS)
	cmake_parse_arguments(pprmc_arg "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

	if("${PONY_TOOLS_INSTALL_DIR}" STREQUAL "")
		message(FATAL_ERROR "PONY_TOOLS_INSTALL_DIR isn't set")
	endif()

	if(${input} STREQUAL "")
		message(FATAL_ERROR "Empty input")
	endif()
	if(${pack_output} STREQUAL "")
		message(FATAL_ERROR "Empty pack output")
	endif()
	if(${manifest_output} STREQUAL "")
		message(FATAL_ERROR "Empty manifest output")
	endif()

	set(PONY_PRMC "${PONY_TOOLS_INSTALL_DIR}/ponyprmc${CMAKE_EXECUTABLE_SUFFIX}")
	if(NOT EXISTS "${PONY_PRMC}")
		message(FATAL_ERROR "'${PONY_PRMC}' not found")
	endif()

	cmake_path(ABSOLUTE_PATH input NORMALIZE OUTPUT_VARIABLE input_abs)
	cmake_path(ABSOLUTE_PATH pack_output NORMALIZE OUTPUT_VARIABLE pack_output_abs)
	cmake_path(ABSOLUTE_PATH manifest_output NORMALIZE OUTPUT_VARIABLE manifest_output_abs)

	check_type_size("std::size_t" SIZEOF_SIZE_T LANGUAGE CXX)
	if(NOT HAVE_SIZEOF_SIZE_T)
		message(FATAL_ERROR "Failed to check sizeof(std::size_t) of the target platform")
	endif()

	set(PPRMC_OPTIONS "")

	if(DEFINED pprmc_arg_ROOT)
		cmake_path(IS_ABSOLUTE "${pprmc_arg_ROOT}" IS_ROOT_ABS)
		if(NOT IS_ROOT_ABS)
			message(FATAL_ERROR "Root path '${pprmc_arg_ROOT}' isn't absolute")
		endif()
		list(APPEND PPRMC_OPTIONS -r "${pprmc_arg_ROOT}")
	endif()

	if(CMAKE_CXX_BYTE_ORDER STREQUAL "BIG_ENDIAN")
		list(APPEND PPRMC_OPTIONS --big-endian)
	endif()

	if(pprmc_arg_ADDITIONAL_PARAMS)
		list(APPEND PPRMC_OPTIONS ${pPrmc_arg_ADDITIONAL_PARAMS})
	endif()

	set(PONY_PRMC_DEPFILE "${manifest_output_abs}.d")
	add_custom_command(COMMAND "${PONY_PRMC}" "${input_abs}" -po "${pack_output_abs}" -mo "${manifest_output_abs}" -d "${PONY_PRMC_DEPFILE}" --size-t ${SIZEOF_SIZE_T} ${PPRMC_OPTIONS}
		DEPENDS "${input_abs}"
		OUTPUT "${pack_output_abs}" "${manifest_output_abs}"
		DEPFILE "${PONY_PRMC_DEPFILE}"
		COMMENT "Compiling '${input}' to '${pack_output}' and '${manifest_output}' with ponyprmc"
		VERBATIM COMMAND_EXPAND_LISTS
	)
endfunction()
