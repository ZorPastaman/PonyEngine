message(STATUS "Configuring MSVC toolchain")
set(CMAKE_CXX_COMPILER "cl.exe")

message(STATUS "Configuring cache flags")
string(REGEX REPLACE "/RTC[^ ]*" "" NEW_DEBUG_FLAGS "${CMAKE_CXX_FLAGS_DEBUG}")
string(REGEX REPLACE "/O[^ ]*" "" NEW_DEBUG_FLAGS "${NEW_DEBUG_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${NEW_DEBUG_FLAGS}" CACHE STRING "Clean debug flags" FORCE)
string(REGEX REPLACE "/O[^ ]*" "" NEW_RELEASE_FLAGS "${CMAKE_CXX_FLAGS_RELEASE}")
set(CMAKE_CXX_FLAGS_RELEASE "${NEW_RELEASE_FLAGS}" CACHE STRING "Clean release flags" FORCE)
string(REGEX REPLACE "/O[^ ]*" "" NEW_RELWITHDEBINFO_FLAGS "${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${NEW_RELWITHDEBINFO_FLAGS}" CACHE STRING "Clean release with debug info flags" FORCE)

# They are needed to compile std module correctly
message(STATUS "Configuring default build flags")
add_compile_options(/arch:AVX2 /EHsc /fp:fast /GR /permissive- /utf-8 /W3 /Zc:__cplusplus /Zc:preprocessor /Zc:throwingNew)
if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
	add_compile_options(/Zi)
endif()
if(PONY_ENGINE_OPTIMIZATION STREQUAL "Debug")
	add_compile_options(/Ob0 /Od /RTC1)
	add_link_options(/INCREMENTAL /OPT:NOREF)
elseif(PONY_ENGINE_OPTIMIZATION STREQUAL "Release")
	add_compile_options(/GL /Gw /Gy /Ob3 /O2 /Zc:inline)
	add_link_options(/INCREMENTAL:NO /LTCG /OPT:REF /OPT:ICF)
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
	target_compile_options(${target_name} PRIVATE /arch:AVX2 /EHsc /fp:fast /GR /permissive- /utf-8 /W3 /Zc:__cplusplus /Zc:preprocessor /Zc:throwingNew)
	if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
		target_compile_options(${target_name} PRIVATE /Zi)
	endif()
	if(${optimization} STREQUAL "Debug")
		target_compile_options(${target_name} PRIVATE /Ob0 /Od /RTC1)
		target_link_options(${target_name} PRIVATE /INCREMENTAL /OPT:NOREF)
	elseif(${optimization} STREQUAL "Release")
		target_compile_options(${target_name} PRIVATE /GL /Gw /Gy /Ob3 /O2 /Zc:inline)
		target_link_options(${target_name} PRIVATE /INCREMENTAL:NO /LTCG /OPT:REF /OPT:ICF)
	else()
		message(FATAL_ERROR "Incorrect optimization type")
	endif()
endfunction()
