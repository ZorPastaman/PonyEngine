# Validates the path.
# path - Path to validate.
# can_be_absolute - Can the path be absolute?
# can_be_relative - Can the path be relative?
function(pony_validate_path path can_be_absolute can_be_relative)
	if(NOT ${path})
		message(FATAL_ERROR "${path} isn't set")
	endif()

	if(IS_ABSOLUTE ${${path}})
		if(NOT ${can_be_absolute})
			message(FATAL_ERROR "${path} can't be absolute")
		endif()
	else()
		if(NOT ${can_be_relative})
			message(FATAL_ERROR "${path} can't be relative")
		endif()
	endif()

	if(NOT ${path} MATCHES "^[A-Za-z0-9._/-]+$")
		message(FATAL_ERROR "${path} contains invalid symbols")
	endif()

	string(REPLACE "/" ";" path_components ${${path}})
	foreach(path_component IN LISTS path_components)
		string(TOLOWER "${path_component}" path_component_lower)
		if("${path_component_lower}" MATCHES "^(con|prn|aux|nul|com[1-9]|lpt[1-9])(\\..*)?$")
			message(FATAL_ERROR "${path} contains invalid component names")
		endif()
	endforeach()
endfunction()
