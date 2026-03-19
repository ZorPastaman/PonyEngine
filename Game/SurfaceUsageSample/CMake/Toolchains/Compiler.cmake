# They are needed to compile std module correctly
if(PONY_ENGINE_OPTIMIZATION STREQUAL "Debug")
	add_compile_options(${PONY_COMPILE_FLAGS_DEBUG})
	add_link_options(${PONY_LINK_FLAGS_DEBUG})
elseif(PONY_ENGINE_OPTIMIZATION STREQUAL "Release")
	add_compile_options(${PONY_COMPILE_FLAGS_RELEASE})
	add_link_options(${PONY_LINK_FLAGS_RELEASE})
endif()

# Cleans build options.
# Must be called after a first project() but before a first target.
function(pony_clean_build_options)
	set_directory_properties(PROPERTIES COMPILE_OPTIONS "")
	set_directory_properties(PROPERTIES LINK_OPTIONS "")
endfunction()

# Sets build options by the optimization level.
# target_name - Target name.
# optimization - Optimization level. May be Debug or Release.
function(pony_set_build_options target_name optimization)
	if(${optimization} STREQUAL "Debug")
		target_compile_options(${target_name} PRIVATE ${PONY_COMPILE_FLAGS_DEBUG})
		target_link_options(${target_name} PRIVATE ${PONY_LINK_FLAGS_DEBUG})
	elseif(${optimization} STREQUAL "Release")
		target_compile_options(${target_name} PRIVATE ${PONY_COMPILE_FLAGS_RELEASE})
		target_link_options(${target_name} PRIVATE ${PONY_LINK_FLAGS_RELEASE})
	else()
		message(FATAL_ERROR "Incorrect optimization type")
	endif()
endfunction()
