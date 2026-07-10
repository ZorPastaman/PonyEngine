# Validates the path.
# path - Path variable to validate.
# CAN_BE_ABSOLUTE - the path can be absolute.
# CAN_BE_RELATIVE - the path can be relative.
function(pony_validate_path path)
	set(options CAN_BE_ABSOLUTE CAN_BE_RELATIVE)
	cmake_parse_arguments(path_arg "${options}" "" "" ${ARGN})

	if(NOT DEFINED ${path} OR ${path} STREQUAL "")
		message(FATAL_ERROR "'${path}' isn't set")
	endif()

	if(IS_ABSOLUTE ${${path}})
		if(NOT path_arg_CAN_BE_ABSOLUTE)
			message(FATAL_ERROR "'${path}' can't be absolute")
		endif()
	else()
		if(NOT path_arg_CAN_BE_RELATIVE)
			message(FATAL_ERROR "'${path}' can't be relative")
		endif()
	endif()

	if(NOT ${path} MATCHES "^[A-Za-z0-9._/-]+$")
		message(FATAL_ERROR "'${path}' contains invalid symbols")
	endif()

	string(REPLACE "/" ";" path_components ${${path}})
	foreach(path_component IN LISTS path_components)
		string(TOLOWER "${path_component}" path_component_lower)
		if("${path_component_lower}" MATCHES "^(con|prn|aux|nul|com[1-9]|lpt[1-9])(\\..*)?$")
			message(FATAL_ERROR "'${path}' contains invalid component names")
		endif()
	endforeach()
endfunction()
