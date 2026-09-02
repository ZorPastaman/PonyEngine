set(PONY_RESOURCE_FILE_PATH_DIR "${CMAKE_CURRENT_BINARY_DIR}/Generated/Data")
set(PONY_RESOURCE_FILE_PATH "${PONY_RESOURCE_FILE_PATH_DIR}/Resources.rc")
file(MAKE_DIRECTORY "${PONY_RESOURCE_FILE_PATH_DIR}")
file(WRITE "${PONY_RESOURCE_FILE_PATH}" "")
set_target_properties(PonyEngine.Application.Impl PROPERTIES PONY_RESOURCE_FILE_PATH "${PONY_RESOURCE_FILE_PATH}")
target_sources(PonyEngine.Application.Impl PRIVATE "${PONY_RESOURCE_FILE_PATH}")

# Adds a resource to a generated .rc file.
# id - resource ID. Must be unique.
# path - path to a resource.
# type - resource type. Must be one of the supported rc types.
function(pony_add_winapi_resource id path type)
	get_target_property(resource_file_path PonyEngine.Application.Impl PONY_RESOURCE_FILE_PATH)
	cmake_path(CONVERT "${path}" TO_NATIVE_PATH_LIST path)
	file(APPEND "${resource_file_path}" "\"${id}\" ${type} \"${path}\"\n")
endfunction()

# Adds an icon to a generated .rc file.
# id - icon ID. Must be unique.
# path = path to an icon.
function(pony_add_winapi_icon id path)
	pony_add_winapi_resource("${id}" "${path}" "ICON")
endfunction()
# Adds a cursor to a generated .rc file.
# id - cursor ID. Must be unique.
# path = path to a cursor.
function(pony_add_winapi_cursor id path)
	pony_add_winapi_resource("${id}" "${path}" "CURSOR")
endfunction()
