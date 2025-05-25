# Sets compile options based on if the target is an engine target or a game target.
# target_name - Target name.
# is_engine_target - Is the target an engine target?
function(set_compile_options target_name is_engine_target)
	function(set_base_options target_name)
		target_compile_options(${target_name} PUBLIC
			$<$<CXX_COMPILER_ID:MSVC>:/W4>
		)
	endfunction()
	function(set_debug_options target_name)
		target_compile_options(${target_name} PUBLIC
			$<$<CXX_COMPILER_ID:MSVC>:/Od /RTC1 /RTCc>
		)
	endfunction()
	function(set_release_in_debug_options target_name)
		target_compile_options(${target_name} PUBLIC
			$<$<CXX_COMPILER_ID:MSVC>:/Ob3>
		)
	endfunction()
	function(set_release_options target_name)
		target_compile_options(${target_name} PUBLIC
			$<$<CXX_COMPILER_ID:MSVC>:/O2 /Ob3>
		)
	endfunction()
	function(set_options target_name optimization)
		if(optimization STREQUAL "Debug")
			set_debug_options(${target_name})
		elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
			set_release_in_debug_options(${target_name})
		else()
			set_release_options(${target_name})
		endif()
	endfunction()

	set_base_options(${target_name})

	if(is_engine_target)
		set_options(${target_name} ${ENGINE_OPTIMIZATION})
	else()
		set_options(${target_name} ${GAME_OPTIMIZATION})
	endif()
endfunction()
