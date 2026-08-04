set(PONY_THREAD_ROLE_SOURCE_FILE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Source/Main-ThreadRole.cppm.in")
set_target_properties(PonyEngine.Application.Impl PROPERTIES PONY_THREAD_ROLE_SOURCE_FILE_PATH "${PONY_THREAD_ROLE_SOURCE_FILE_PATH}")
set(PONY_THREAD_ROLE_TARGET_FILE_PATH "${CMAKE_CURRENT_BINARY_DIR}/Generated/Source/Main-ThreadRole.cppm")
set_target_properties(PonyEngine.Application.Impl PROPERTIES PONY_THREAD_ROLE_TARGET_FILE_PATH "${PONY_THREAD_ROLE_TARGET_FILE_PATH}")
configure_file("${PONY_THREAD_ROLE_SOURCE_FILE_PATH}" "${PONY_THREAD_ROLE_TARGET_FILE_PATH}")
target_sources(PonyEngine.Application.Impl PRIVATE FILE_SET CXX_MODULES BASE_DIRS "${CMAKE_CURRENT_BINARY_DIR}" FILES "${PONY_THREAD_ROLE_TARGET_FILE_PATH}")
set_target_properties(PonyEngine.Application.Impl PROPERTIES PONY_THREAD_ROLES "")

# Adds a thread role.
# id - Role ID.
# thread_priority - basic thread priority.
# MMCSS_TASK - optional mmcss task name.
# MMCSS_PRIORITY - optional mmcss priority.
function(pony_add_thread_role id thread_priority)
	set(oneValueArgs MMCSS_TASK MMCSS_PRIORITY)
	cmake_parse_arguments(role_arg "" "${oneValueArgs}" "" ${ARGN})

	if(NOT DEFINED role_arg_MMCSS_TASK)
		set(role_arg_MMCSS_TASK "")
		set(role_arg_MMCSS_PRIORITY "AVRT_PRIORITY_NORMAL")
	endif()

	get_target_property(thread_roles PonyEngine.Application.Impl PONY_THREAD_ROLES)
	string(APPEND thread_roles
		"		{ \"${id}\", ThreadRole {.threadPriority = ${thread_priority}, .mmcssPriority = ${role_arg_MMCSS_PRIORITY}, .mmcssTask = \"${role_arg_MMCSS_TASK}\" } },\n"
	)
	set_target_properties(PonyEngine.Application.Impl PROPERTIES PONY_THREAD_ROLES "${thread_roles}")

	get_target_property(thread_role_source_file_path PonyEngine.Application.Impl PONY_THREAD_ROLE_SOURCE_FILE_PATH)
	get_target_property(thread_role_target_file_path PonyEngine.Application.Impl PONY_THREAD_ROLE_TARGET_FILE_PATH)
	set(PONY_APPLICATION_THREAD_ROLES "${thread_roles}")
	configure_file("${thread_role_source_file_path}" "${thread_role_target_file_path}")
endfunction()

option(PONY_ENGINE_APPLICATION_SET_DEFAULT_THREAD_ROLES "If true, the default thread roles are added automatically." ON)
if(PONY_ENGINE_APPLICATION_SET_DEFAULT_THREAD_ROLES)
	pony_add_thread_role("Main" "THREAD_PRIORITY_ABOVE_NORMAL" MMCSS_TASK "Games" MMCSS_PRIORITY "AVRT_PRIORITY_NORMAL")
	pony_add_thread_role("Render" "THREAD_PRIORITY_ABOVE_NORMAL" MMCSS_TASK "Games" MMCSS_PRIORITY "AVRT_PRIORITY_HIGH")
	pony_add_thread_role("Audio" "THREAD_PRIORITY_HIGHEST" MMCSS_TASK "Audio" MMCSS_PRIORITY "AVRT_PRIORITY_CRITICAL")
	pony_add_thread_role("Worker" "THREAD_PRIORITY_NORMAL")
	pony_add_thread_role("AsyncTask" "THREAD_PRIORITY_NORMAL")
	pony_add_thread_role("IO" "THREAD_PRIORITY_NORMAL")
	pony_add_thread_role("Background" "THREAD_PRIORITY_BELOW_NORMAL")
endif()

set(PONY_ENGINE_APPLICATION_MAIN_THREAD_ROLE "Main" CACHE STRING "Main thread role. If empty or false, no role is applied.")
target_compile_definitions(PonyEngine.Application.Impl PRIVATE
	$<$<BOOL:${PONY_ENGINE_APPLICATION_MAIN_THREAD_ROLE}>:PONY_ENGINE_APPLICATION_MAIN_THREAD_ROLE=${PONY_ENGINE_APPLICATION_MAIN_THREAD_ROLE}>
)
