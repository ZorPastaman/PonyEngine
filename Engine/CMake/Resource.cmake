# Creates a file resource manifest.
# path - manifest path.
# ADDITIONAL_PARAMS - any parameters that are added as pure text to a command line.
function(pony_create_file_resource_manifest path)
	set(multiValueArgs ADDITIONAL_PARAMS)
	cmake_parse_arguments(pfrmg_arg "" "" "${multiValueArgs}" ${ARGN})

	if(NOT DEFINED PONY_TOOLS_INSTALL_DIR OR "${PONY_TOOLS_INSTALL_DIR}" STREQUAL "")
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

# Adds resources to a file resource manifest.
# path - manifest path.
# RESOURCES - resource list. Each resource must be in the format: '<id>,<type>,<path>'.
#             The string can be easily generated with the 'pony_make_resource_for_file_resource_manifest' function.
# ADDITIONAL_PARAMS - any parameters that are added as pure text to a command line.
function(pony_add_to_file_resource_manifest path)
	set(multiValueArgs RESOURCES ADDITIONAL_PARAMS)
	cmake_parse_arguments(pfrmg_arg "" "" "${multiValueArgs}" ${ARGN})

	if(NOT DEFINED PONY_TOOLS_INSTALL_DIR OR "${PONY_TOOLS_INSTALL_DIR}" STREQUAL "")
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

# Removes resources from a file resource manifest.
# path - manifest path.
# IDS - resource ids to remove.
# ADDITIONAL_PARAMS - any parameters that are added as pure text to a command line.
function(pony_remove_from_file_resource_manifest path)
	set(multiValueArgs IDS ADDITIONAL_PARAMS)
	cmake_parse_arguments(pfrmg_arg "" "" "${multiValueArgs}" ${ARGN})

	if(NOT DEFINED PONY_TOOLS_INSTALL_DIR OR "${PONY_TOOLS_INSTALL_DIR}" STREQUAL "")
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

# Upgrades a file resource manifest to an actual version.
# path - manifest path.
# ADDITIONAL_PARAMS - any parameters that are added as pure text to a command line.
function(pony_upgrade_file_resource_manifest path)
	set(multiValueArgs ADDITIONAL_PARAMS)
	cmake_parse_arguments(pfrmg_arg "" "" "${multiValueArgs}" ${ARGN})

	if(NOT DEFINED PONY_TOOLS_INSTALL_DIR OR "${PONY_TOOLS_INSTALL_DIR}" STREQUAL "")
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

# Makes a resource string for a file resource manifest.
# id - resource ID.
# type - resource type.
# path - resource path.
# resource - output variable that will hold the resource string.
function(pony_make_resource_for_file_resource_manifest id type path resource)
	set(${resource} "${id},${type},${path}" PARENT_SCOPE)
endfunction()

# Compiles a file resource manifest.
# input - path to a text resource manifest.
# output - path to binary resource manifest.
# ADDITIONAL_PARAMS - any parameters that are added as pure text to a command line.
function(pony_compile_file_resource_manifest input output)
	set(multiValueArgs ADDITIONAL_PARAMS)
	cmake_parse_arguments(pfrmc_arg "" "" "${multiValueArgs}" ${ARGN})

	if(NOT DEFINED PONY_TOOLS_INSTALL_DIR OR "${PONY_TOOLS_INSTALL_DIR}" STREQUAL "")
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

# Creates a pack resource manifest.
# manifest_path - path to a created resource manifest.
# pack_path - path to a runtime pack.
# ADDITIONAL_PARAMS - any parameters that are added as pure text to a command line.
function(pony_create_pack_resource_manifest manifest_path pack_path)
	set(multiValueArgs ADDITIONAL_PARAMS)
	cmake_parse_arguments(pprmg_arg "" "" "${multiValueArgs}" ${ARGN})

	if(NOT DEFINED PONY_TOOLS_INSTALL_DIR OR "${PONY_TOOLS_INSTALL_DIR}" STREQUAL "")
		message(FATAL_ERROR "PONY_TOOLS_INSTALL_DIR isn't set")
	endif()

	if("${manifest_path}" STREQUAL "")
		message(FATAL_ERROR "Empty manifest path")
	endif()
	if("${pack_path}" STREQUAL "")
		message(FATAL_ERROR "Empty pack path")
	endif()

	set(PONY_PRMG "${PONY_TOOLS_INSTALL_DIR}/ponyprmg${CMAKE_EXECUTABLE_SUFFIX}")
	if(NOT EXISTS "${PONY_PRMG}")
		message(FATAL_ERROR "'${PONY_PRMG}' not found")
	endif()

	cmake_path(ABSOLUTE_PATH manifest_path NORMALIZE OUTPUT_VARIABLE manifest_path_abs)

	set(PPRMG_OPTIONS "")

	if(pprmg_arg_ADDITIONAL_PARAMS)
		list(APPEND PPRMG_OPTIONS ${pprmg_arg_ADDITIONAL_PARAMS})
	endif()

	message(STATUS "Creating '${manifest_path}' with ponyprmg")
	execute_process(COMMAND "${PONY_PRMG}" "${manifest_path_abs}" --create "${pack_path}" ${PPRMG_OPTIONS}
		COMMAND_ERROR_IS_FATAL ANY
	)
endfunction()

# Adds resources to a pack resource manifest.
# path - manifest path.
# RESOURCES - resource list. Each resource must be in the format: '<id>,<type>,<path>'.
#             The string can be easily generated with the 'pony_make_resource_for_pack_resource_manifest' function.
# ADDITIONAL_PARAMS - any parameters that are added as pure text to a command line.
function(pony_add_to_pack_resource_manifest path)
	set(multiValueArgs RESOURCES ADDITIONAL_PARAMS)
	cmake_parse_arguments(pprmg_arg "" "" "${multiValueArgs}" ${ARGN})

	if(NOT DEFINED PONY_TOOLS_INSTALL_DIR OR "${PONY_TOOLS_INSTALL_DIR}" STREQUAL "")
		message(FATAL_ERROR "PONY_TOOLS_INSTALL_DIR isn't set")
	endif()

	if("${path}" STREQUAL "")
		message(FATAL_ERROR "Empty path")
	endif()

	set(PONY_PRMG "${PONY_TOOLS_INSTALL_DIR}/ponyprmg${CMAKE_EXECUTABLE_SUFFIX}")
	if(NOT EXISTS "${PONY_PRMG}")
		message(FATAL_ERROR "'${PONY_PRMG}' not found")
	endif()

	if(NOT pprmg_arg_RESOURCES)
		return()
	endif()

	cmake_path(ABSOLUTE_PATH path NORMALIZE OUTPUT_VARIABLE path_abs)

	set(ADD_LIST "")
	foreach(RESOURCE IN LISTS pprmg_arg_RESOURCES)
		list(APPEND ADD_LIST --add "${RESOURCE}")
	endforeach()

	set(PPRMG_OPTIONS "")

	if(pprmg_arg_ADDITIONAL_PARAMS)
		list(APPEND PPRMG_OPTIONS ${pprmg_arg_ADDITIONAL_PARAMS})
	endif()

	message(STATUS "Adding '${pprmg_arg_RESOURCES}' to '${path}' with ponyprmg")
	execute_process(COMMAND "${PONY_PRMG}" "${path_abs}" ${ADD_LIST} ${PPRMG_OPTIONS}
		COMMAND_ERROR_IS_FATAL ANY
	)
endfunction()

# Removes resources from a pack resource manifest.
# path - manifest path.
# IDS - resource ids to remove.
# ADDITIONAL_PARAMS - any parameters that are added as pure text to a command line.
function(pony_remove_from_pack_resource_manifest path)
	set(multiValueArgs IDS ADDITIONAL_PARAMS)
	cmake_parse_arguments(pprmg_arg "" "" "${multiValueArgs}" ${ARGN})

	if(NOT DEFINED PONY_TOOLS_INSTALL_DIR OR "${PONY_TOOLS_INSTALL_DIR}" STREQUAL "")
		message(FATAL_ERROR "PONY_TOOLS_INSTALL_DIR isn't set")
	endif()

	if("${path}" STREQUAL "")
		message(FATAL_ERROR "Empty path")
	endif()

	set(PONY_PRMG "${PONY_TOOLS_INSTALL_DIR}/ponyprmg${CMAKE_EXECUTABLE_SUFFIX}")
	if(NOT EXISTS "${PONY_PRMG}")
		message(FATAL_ERROR "'${PONY_PRMG}' not found")
	endif()

	if(NOT pprmg_arg_IDS)
		return()
	endif()

	cmake_path(ABSOLUTE_PATH path NORMALIZE OUTPUT_VARIABLE path_abs)

	set(REMOVE_LIST "")
	foreach(ID IN LISTS pprmg_arg_IDS)
		list(APPEND REMOVE_LIST --remove "${ID}")
	endforeach()

	set(PPRMG_OPTIONS "")

	if(pprmg_arg_ADDITIONAL_PARAMS)
		list(APPEND PPRMG_OPTIONS ${pprmg_arg_ADDITIONAL_PARAMS})
	endif()

	message(STATUS "Removing '${pprmg_arg_IDS}' from '${path}' with ponyprmg")
	execute_process(COMMAND "${PONY_PRMG}" "${path_abs}" ${REMOVE_LIST} ${PPRMG_OPTIONS}
		COMMAND_ERROR_IS_FATAL ANY
	)
endfunction()

# Upgrades a pack resource manifest to an actual version.
# path - manifest path.
# ADDITIONAL_PARAMS - any parameters that are added as pure text to a command line.
function(pony_upgrade_pack_resource_manifest path)
	set(multiValueArgs ADDITIONAL_PARAMS)
	cmake_parse_arguments(pprmg_arg "" "" "${multiValueArgs}" ${ARGN})

	if(NOT DEFINED PONY_TOOLS_INSTALL_DIR OR "${PONY_TOOLS_INSTALL_DIR}" STREQUAL "")
		message(FATAL_ERROR "PONY_TOOLS_INSTALL_DIR isn't set")
	endif()

	if("${path}" STREQUAL "")
		message(FATAL_ERROR "Empty path")
	endif()

	set(PONY_PRMG "${PONY_TOOLS_INSTALL_DIR}/ponyprmg${CMAKE_EXECUTABLE_SUFFIX}")
	if(NOT EXISTS "${PONY_PRMG}")
		message(FATAL_ERROR "'${PONY_PRMG}' not found")
	endif()

	cmake_path(ABSOLUTE_PATH path NORMALIZE OUTPUT_VARIABLE path_abs)

	set(PPRMG_OPTIONS "")

	if(pprmg_arg_ADDITIONAL_PARAMS)
		list(APPEND PPRMG_OPTIONS ${pprmg_arg_ADDITIONAL_PARAMS})
	endif()

	message(STATUS "Upgrading '${path}' with ponyprmg")
	execute_process(COMMAND "${PONY_PRMG}" "${path_abs}" --upgrade ${PPRMG_OPTIONS}
		COMMAND_ERROR_IS_FATAL ANY
	)
endfunction()

# Makes a resource string for a pack resource manifest.
# id - resource ID.
# type - resource type.
# path - resource path.
# resource - output variable that will hold the resource string.
function(pony_make_resource_for_pack_resource_manifest id type path resource)
	set(${resource} "${id},${type},${path}" PARENT_SCOPE)
endfunction()

# Compiles a pack resource manifest.
# input - path to a text resource manifest.
# pack_output - path to binary resource pack.
# manifest_output - path to a binary resource manifest.
# ROOT - Root path of resources in the source manifest. If not set, the parent of the input resource manifest will be used.
# ADDITIONAL_PARAMS - any parameters that are added as pure text to a command line.
function(pony_compile_pack_resource_manifest input pack_output manifest_output)
	set(oneValueArgs ROOT)
	set(multiValueArgs ADDITIONAL_PARAMS)
	cmake_parse_arguments(pprmc_arg "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

	if(NOT DEFINED PONY_TOOLS_INSTALL_DIR OR "${PONY_TOOLS_INSTALL_DIR}" STREQUAL "")
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

	if(NOT PONY_SIZEOF_SIZE_T)
		message(FATAL_ERROR "Failed to check sizeof(std::size_t) of the target platform")
	endif()

	set(PPRMC_OPTIONS "")

	if(DEFINED pprmc_arg_ROOT)
		cmake_path(IS_ABSOLUTE pprmc_arg_ROOT IS_ROOT_ABS)
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
	add_custom_command(COMMAND "${PONY_PRMC}" "${input_abs}" -po "${pack_output_abs}" -mo "${manifest_output_abs}" -d "${PONY_PRMC_DEPFILE}" --size-t ${PONY_SIZEOF_SIZE_T} ${PPRMC_OPTIONS}
		DEPENDS "${input_abs}"
		OUTPUT "${pack_output_abs}" "${manifest_output_abs}"
		DEPFILE "${PONY_PRMC_DEPFILE}"
		COMMENT "Compiling '${input}' to '${pack_output}' and '${manifest_output}' with ponyprmc"
		VERBATIM COMMAND_EXPAND_LISTS
	)
endfunction()
