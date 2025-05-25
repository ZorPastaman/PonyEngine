# Cleans default optimization flags.
function(init_compile_options)
if (MSVC)
	string(REGEX REPLACE "/RTC[^ ]*" "" NEW_DEBUG_FLAGS "${CMAKE_CXX_FLAGS_DEBUG}")
	string(REGEX REPLACE "/O[^ ]*" "" NEW_DEBUG_FLAGS "${NEW_DEBUG_FLAGS}")
	set(CMAKE_CXX_FLAGS_DEBUG "${NEW_DEBUG_FLAGS}" CACHE STRING "Clean debug flags" FORCE)

	string(REGEX REPLACE "/O[^ ]*" "" NEW_RELEASE_FLAGS "${CMAKE_CXX_FLAGS_RELEASE}")
	set(CMAKE_CXX_FLAGS_RELEASE "${NEW_RELEASE_FLAGS}" CACHE STRING "Clean release flags" FORCE)

	string(REGEX REPLACE "/O[^ ]*" "" NEW_RELWITHDEBINFO_FLAGS "${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${NEW_RELWITHDEBINFO_FLAGS}" CACHE STRING "Clean release with debug info flags" FORCE)
endif()
endfunction()

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
			$<$<CXX_COMPILER_ID:MSVC>:/Ob0 /Od /RTC1 /RTCc>
		)
	endfunction()
	function(set_release_options target_name)
		target_compile_options(${target_name} PUBLIC
			$<$<CXX_COMPILER_ID:MSVC>:/Ob3 /O2>
		)
	endfunction()
	function(set_options target_name optimization)
		if(optimization STREQUAL "Debug")
			set_debug_options(${target_name})
		elseif(optimization STREQUAL "Release")
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
