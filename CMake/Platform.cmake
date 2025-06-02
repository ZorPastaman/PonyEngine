# Sets platform defines.
function(pony_init_platform)
	if(PONY_WINCORE)
		add_compile_definitions(PONY_WINCORE)
	endif()
	if(PONY_WINDOWS)
		add_compile_definitions(PONY_WINDOWS)
	endif()
endfunction()
