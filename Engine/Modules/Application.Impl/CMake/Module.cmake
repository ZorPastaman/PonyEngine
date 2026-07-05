# Adds the modules to the application.
# Pass targets to the function.
function(pony_add_application_modules)
	message(STATUS "Adding application modules: '${ARGN}'")

	foreach(MODULE IN LISTS ARGN)
		if(NOT TARGET ${MODULE})
			message(FATAL_ERROR "Invalid module: '${MODULE}'")
		endif()
	endforeach()

	target_link_libraries(PonyEngine.Application.Impl PRIVATE ${ARGN})
endfunction()
