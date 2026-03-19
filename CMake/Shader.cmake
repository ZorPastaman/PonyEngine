function(compile_shader_with_dxc source output profile)
	set(options SPIRV PDB ENABLE_16_BIT)
	set(oneValueArgs ROOT_SIG_VER ENTRY OPTIMIZATION SPIRV_TARGET)
	set(multiValueArgs DEFINES INCLUDES ADDITIONAL_PARAMS)
	cmake_parse_arguments(PARSE_ARGV 0 dxc_arg "${options}" "${oneValueArgs}" "${multiValueArgs}")

	if(NOT source)
		message(FATAL_ERROR "Empty source")
	endif()
	if(NOT output)
		message(FATAL_ERROR "Empty output")
	endif()
	if(NOT profile)
		message(FATAL_ERROR "Empty profile")
	endif()

	if(dxc_arg_SPIRV_TARGET AND NOT dxc_arg_SPIRV)
		message(FATAL_ERROR "SPIR-V target is set in non-spirv build")
	endif()

	get_filename_component(source_abs ${source} ABSOLUTE)
	get_filename_component(output_abs ${output} ABSOLUTE)

	if(NOT dxc_arg_ENTRY)
		set(dxc_arg_ENTRY "main")
	endif()

	get_filename_component(output_dir ${output_abs} DIRECTORY)
	file(MAKE_DIRECTORY ${output_dir})
	set(DXC_OPTIONS -T ${profile} -E ${dxc_arg_ENTRY} -Fo ${output_abs})
	if(dxc_arg_ROOT_SIG_VER)
		list(APPEND DXC_OPTIONS -force-rootsig-ver ${dxc_arg_ROOT_SIG_VER})
	endif()
	if(dxc_arg_OPTIMIZATION)
		list(APPEND DXC_OPTIONS -O${dxc_arg_OPTIMIZATION})
	endif()
	foreach(define ${dxc_arg_DEFINES})
		list(APPEND DXC_OPTIONS -D ${define})
	endforeach()
	foreach(include ${dxc_arg_INCLUDES})
		get_filename_component(include_abs ${include} ABSOLUTE)
		list(APPEND DXC_OPTIONS -I ${include_abs})
	endforeach()

	if(dxc_arg_ENABLE_16_BIT)
		list(APPEND DXC_OPTIONS -enable-16bit-types)
	endif()

	if(dxc_arg_SPIRV)
		list(APPEND DXC_OPTIONS -spirv)
		list(APPEND DXC_OPTIONS -D PONY_SPIRV)
	else()
		list(APPEND DXC_OPTIONS -D PONY_DIXL)
	endif()
	if(dxc_arg_SPIRV_TARGET)
		list(APPEND DXC_OPTIONS -fspv-target-env=${dxc_arg_SPIRV_TARGET})
	endif()

	if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
		list(APPEND DXC_OPTIONS -Zi)
		if(dxc_arg_PDB)
			list(APPEND DXC_OPTIONS -Fd ${output_abs}.pdb)
		else()
			list(APPEND DXC_OPTIONS -Qembed_debug)
		endif()
	else()
		list(APPEND DXC_OPTIONS -Qstrip_debug -Qstrip_reflect)
		set(dxc_arg_PDB OFF)
	endif()

	if(dxc_arg_ADDITIONAL_PARAMS)
		list(APPEND DXC_OPTIONS ${dxc_arg_ADDITIONAL_PARAMS})
	endif()

	set(DXC_DEP_FILE ${output_abs}.d)
	add_custom_command(COMMAND dxc ${DXC_OPTIONS} -MD -MF ${DXC_DEP_FILE} ${source_abs} && dxc ${DXC_OPTIONS} ${source_abs}
		DEPENDS ${source_abs}
		OUTPUT ${output_abs}
		DEPFILE ${DXC_DEP_FILE}
		COMMENT "Compiling ${source} to ${output} with dxc"
		VERBATIM
	)
endfunction()
