# Cleans default build flags.
function(pony_init_build_options)
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

# Sets build options based on if the target is an engine target or a game target.
# target_name - Target name.
# is_engine_target - Is the target an engine target?
function(pony_set_build_options target_name is_engine_target)
	function(set_base_options target_name)
		target_compile_options(${target_name} PUBLIC
			$<$<CXX_COMPILER_ID:MSVC>:/arch:AVX2 /EHsc /fp:fast /GR /W4 /permissive- /utf-8 /Zc:__cplusplus /Zc:preprocessor /Zc:throwingNew>
		)

		if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
			target_compile_options(${target_name} PUBLIC
				$<$<CXX_COMPILER_ID:MSVC>:/Zi>
			)
		elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
		else()
			message(FATAL_ERROR "Incorrect build type")
		endif()
	endfunction()

	function(set_debug_options target_name)
		target_compile_options(${target_name} PUBLIC
			$<$<CXX_COMPILER_ID:MSVC>:/Ob0 /Od /RTC1>
		)
		target_link_options(${target_name} PUBLIC
			$<$<CXX_COMPILER_ID:MSVC>:/INCREMENTAL /OPT:NOREF>
		)
	endfunction()
	function(set_release_options target_name)
		target_compile_options(${target_name} PUBLIC
			$<$<CXX_COMPILER_ID:MSVC>:/GL /Gw /Gy /Ob3 /O2 /Zc:inline>
		)
		target_link_options(${target_name} PUBLIC
			$<$<CXX_COMPILER_ID:MSVC>:/INCREMENTAL:NO /LTCG /OPT:REF /OPT:ICF>
		)
	endfunction()
	function(set_options target_name optimization)
		set_base_options(${target_name})

		if(optimization STREQUAL "Debug")
			message(STATUS "Setting debug options")
			set_debug_options(${target_name})
		elseif(optimization STREQUAL "Release")
			message(STATUS "Setting release options")
			set_release_options(${target_name})
		else()
			message(FATAL_ERROR "Incorrect optimization type")
		endif()
	endfunction()

	if(is_engine_target)
		set_options(${target_name} ${PONY_ENGINE_OPTIMIZATION})
	else()
		set_options(${target_name} ${PONY_GAME_OPTIMIZATION})
	endif()
endfunction()
