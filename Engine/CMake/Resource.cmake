function(pony_create_file_resource_manifest path)
	set(multiValueArgs ADDITIONAL_PARAMS)
	cmake_parse_arguments(pfrmg_arg "" "" "${multiValueArgs}" ${ARGN})

	if(NOT path)
		message(FATAL_ERROR "Empty path")
	endif()

	set(PONY_FRMG "${PONY_TOOLS_INSTALL_DIR}/ponyfrmg${CMAKE_EXECUTABLE_SUFFIX}")
	if(NOT EXISTS ${PONY_FRMG})
		message(FATAL_ERROR "${PONY_FRMG} not found")
	endif()

	get_filename_component(path_abs ${path} ABSOLUTE)

	set(PFRMG_OPTIONS "")

	if(pfrmg_arg_ADDITIONAL_PARAMS)
		list(APPEND PFRMG_OPTIONS ${pfrmg_arg_ADDITIONAL_PARAMS})
	endif()

	message(STATUS "Creating ${path} with ponyfrmg")
	execute_process(COMMAND ${PONY_FRMG} ${path_abs} --create ${PFRMG_OPTIONS}
		COMMAND_ERROR_IS_FATAL ANY
	)
endfunction()

function(pony_add_to_file_resource_manifest path)
	set(multiValueArgs RESOURCES ADDITIONAL_PARAMS)
	cmake_parse_arguments(pfrmg_arg "" "" "${multiValueArgs}" ${ARGN})

	if(NOT path)
		message(FATAL_ERROR "Empty path")
	endif()

	set(PONY_FRMG "${PONY_TOOLS_INSTALL_DIR}/ponyfrmg${CMAKE_EXECUTABLE_SUFFIX}")
	if(NOT EXISTS ${PONY_FRMG})
		message(FATAL_ERROR "${PONY_FRMG} not found")
	endif()

	if(NOT pfrmg_arg_RESOURCES)
		return()
	endif()

	get_filename_component(path_abs ${path} ABSOLUTE)

	set(ADD_LIST "")
	foreach(RESOURCE IN LISTS pfrmg_arg_RESOURCES)
		list(APPEND ADD_LIST --add ${RESOURCE})
	endforeach()

	set(PFRMG_OPTIONS "")

	if(pfrmg_arg_ADDITIONAL_PARAMS)
		list(APPEND PFRMG_OPTIONS ${pfrmg_arg_ADDITIONAL_PARAMS})
	endif()

	message(STATUS "Adding ${pfrmg_arg_RESOURCES} to ${path} with ponyfrmg")
	execute_process(COMMAND ${PONY_FRMG} ${path_abs} ${ADD_LIST} ${PFRMG_OPTIONS}
		COMMAND_ERROR_IS_FATAL ANY
	)
endfunction()

function(pony_remove_from_file_resource_manifest path)
	set(multiValueArgs IDS ADDITIONAL_PARAMS)
	cmake_parse_arguments(pfrmg_arg "" "" "${multiValueArgs}" ${ARGN})

	if(NOT path)
		message(FATAL_ERROR "Empty path")
	endif()

	set(PONY_FRMG "${PONY_TOOLS_INSTALL_DIR}/ponyfrmg${CMAKE_EXECUTABLE_SUFFIX}")
	if(NOT EXISTS ${PONY_FRMG})
		message(FATAL_ERROR "${PONY_FRMG} not found")
	endif()

	if(NOT pfrmg_arg_IDS)
		return()
	endif()

	get_filename_component(path_abs ${path} ABSOLUTE)

	set(REMOVE_LIST "")
	foreach(ID IN LISTS pfrmg_arg_IDS)
		list(APPEND REMOVE_LIST --remove ${ID})
	endforeach()

	set(PFRMG_OPTIONS "")

	if(pfrmg_arg_ADDITIONAL_PARAMS)
		list(APPEND PFRMG_OPTIONS ${pfrmg_arg_ADDITIONAL_PARAMS})
	endif()

	message(STATUS "Removing ${pfrmg_arg_IDS} from ${path} with ponyfrmg")
	execute_process(COMMAND ${PONY_FRMG} ${path_abs} ${REMOVE_LIST} ${PFRMG_OPTIONS}
		COMMAND_ERROR_IS_FATAL ANY
	)
endfunction()

function(pony_upgrade_file_resource_manifest path)
	set(multiValueArgs ADDITIONAL_PARAMS)
	cmake_parse_arguments(pfrmg_arg "" "" "${multiValueArgs}" ${ARGN})

	if(NOT path)
		message(FATAL_ERROR "Empty path")
	endif()

	set(PONY_FRMG "${PONY_TOOLS_INSTALL_DIR}/ponyfrmg${CMAKE_EXECUTABLE_SUFFIX}")
	if(NOT EXISTS ${PONY_FRMG})
		message(FATAL_ERROR "${PONY_FRMG} not found")
	endif()

	get_filename_component(path_abs ${path} ABSOLUTE)

	set(PFRMG_OPTIONS "")

	if(pfrmg_arg_ADDITIONAL_PARAMS)
		list(APPEND PFRMG_OPTIONS ${pfrmg_arg_ADDITIONAL_PARAMS})
	endif()

	message(STATUS "Upgrading ${path} with ponyfrmg")
	execute_process(COMMAND ${PONY_FRMG} ${path_abs} --upgrade ${PFRMG_OPTIONS}
		COMMAND_ERROR_IS_FATAL ANY
	)
endfunction()

function(pony_make_resource_for_file_resource_manifest id type path resource)
	set(${resource} "${id},${type},${path}" PARENT_SCOPE)
endfunction()

function(pony_compile_file_resource_manifest input output)
	set(multiValueArgs ADDITIONAL_PARAMS)
	cmake_parse_arguments(pfrmc_arg "" "" "${multiValueArgs}" ${ARGN})

	if(NOT PONY_TOOLS_INSTALL_DIR)
		message(FATAL_ERROR "PONY_TOOLS_INSTALL_DIR isn't set")
	endif()
	if(NOT input)
		message(FATAL_ERROR "Empty source")
	endif()
	if(NOT output)
		message(FATAL_ERROR "Empty output")
	endif()

	set(PONY_FRMC "${PONY_TOOLS_INSTALL_DIR}/ponyfrmc${CMAKE_EXECUTABLE_SUFFIX}")
	if(NOT EXISTS ${PONY_FRMC})
		message(FATAL_ERROR "${PONY_FRMC} not found")
	endif()

	get_filename_component(input_abs ${input} ABSOLUTE)
	get_filename_component(output_abs ${output} ABSOLUTE)

	set(PFRMC_OPTIONS "")

	if(pfrmc_arg_ADDITIONAL_PARAMS)
		list(APPEND PFRMC_OPTIONS ${pfrmc_arg_ADDITIONAL_PARAMS})
	endif()

	add_custom_command(COMMAND ${PONY_FRMC} ${input_abs} -o ${output_abs} ${PFRMC_OPTIONS}
		DEPENDS ${input_abs}
		OUTPUT ${output_abs}
		COMMENT "Compiling ${source} to ${output} with ponyfrmc"
		VERBATIM
	)
endfunction()
