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
