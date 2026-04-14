# Validates the name.
# name - Name to validate.
function(pony_validate_name name)
	if(NOT ${name})
		message(FATAL_ERROR "${name} isn't set")
	endif()

	pony_validate_path(${name} false true)

	string(SUBSTRING ${${name}} 0 1 NAME_FIRST_CHAR)
	if(NAME_FIRST_CHAR STREQUAL "." OR ${name} MATCHES "/")
		message(FATAL_ERROR "${name} is an invalid name")
	endif()
endfunction()

# Validates the title.
# title - Title to validate.
function(pony_validate_title title)
	if(NOT ${title})
		message(FATAL_ERROR "${title} isn't set")
	endif()
endfunction()

# Validates the version.
# version - Version to validate.
function(pony_validate_version version)
	if(NOT ${version})
		message(FATAL_ERROR "${version} isn't set")
	endif()

	if(NOT ${version} MATCHES "^[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+$")
		message(FATAL_ERROR "${version} has invalid format. Correct format is: <number>.<number>.<number>.<number>")
	endif()
endfunction()
