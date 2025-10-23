# Validates the module order.
# module_order - Module order.
function(pony_validate_module_order module_order)
	if(NOT ${module_order})
		message(FATAL_ERROR "${module_order} isn't set")
	endif()

	string(SUBSTRING ${${module_order}} 0 1 ORDER_FIRST_CHAR)
	if(NOT ORDER_FIRST_CHAR MATCHES "^[b-y]$")
		message(FATAL_ERROR "${module_order} is incorrect. Its first letter must be inside b-y range")
	endif()	
endfunction()
