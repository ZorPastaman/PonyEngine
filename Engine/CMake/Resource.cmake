# Adds load resource info to the load_list in the correct format.
# load_params - Load parameters file path.
# load_output - Load output file path.
# load_list - result variable name.
macro(pony_add_resource_load load_params load_output load_list)
	list(APPEND ${load_list} "${load_params}" "${load_output}")
endmacro()

# Adds a resource to a resource list file.
# id - resource ID.
# data - path to a resource container data.
# load - path to a resource container load.
# resource_list - path to a resource list file.
function(pony_add_resource id data load resource_list)
	cmake_path(ABSOLUTE_PATH data OUTPUT_VARIABLE data_abs)
	cmake_path(ABSOLUTE_PATH load OUTPUT_VARIABLE load_abs)

	file(APPEND "${resource_list}" "\"${id}\" \"${data_abs}\" \"${load_abs}\"\n")
endfunction()
