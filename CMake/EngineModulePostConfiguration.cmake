function(pony_apply_flags target engine_target)
	if(${engine_target})
		set(log_level ${PONY_ENGINE_LOG_LEVEL})
		set(stacktrace_level ${PONY_ENGINE_LOG_STACKTRACE_LEVEL})
		set(optimization ${PONY_ENGINE_OPTIMIZATION})
	else()
		set(log_level ${PONY_GAME_LOG_LEVEL})
		set(stacktrace_level ${PONY_GAME_LOG_STACKTRACE_LEVEL})
		set(optimization ${PONY_GAME_OPTIMIZATION})
	endif()

	if(TARGET ${target})
		pony_set_log_defines(${target} ${log_level} ${stacktrace_level})
		pony_set_build_options(${target} ${optimization})
	endif()
endfunction()

macro(pony_add_to_module_list target module_list)
	if(TARGET ${target})
		list(APPEND ${module_list} ${target})
	endif()
endmacro()

macro(pony_manage_module_group module_list group_target engine_target intall_targets)
	if(${module_list})
		pony_make_module_group(${group_target} MODULES ${${module_list}})
		pony_apply_flags(${group_target} ${engine_target})
		pony_add_application_modules(${group_target})
		list(APPEND ${intall_targets} ${group_target})
	endif()
endmacro()

if(NOT TARGET PonyEngine.Application.Impl)
	message(FATAL_ERROR "PonyEngine.Application.Impl wasn't added to the engine build")
endif()

set(PONY_BASE_MODULES "")
set(PONY_LOG_MODULES "")
set(PONY_PLATFORM_MODULES "")
set(PONY_INPUT_MODULES "")
set(PONY_RENDER_MODULES "")
set(PONY_RESOURCE_MODULES "")
set(PONY_LOGIC_MODULES "")

message(VERBOSE "Post-configuring")
pony_apply_flags(PonyEngine.Core TRUE)
pony_apply_flags(PonyEngine.Log TRUE)
pony_apply_flags(PonyEngine.Application TRUE)
pony_apply_flags(PonyEngine.Application.Impl TRUE)

pony_apply_flags(PonyEngine.Time TRUE)
pony_apply_flags(PonyEngine.Time.Impl TRUE)
pony_add_to_module_list(PonyEngine.Time.Impl PONY_BASE_MODULES)

pony_apply_flags(PonyEngine.Job TRUE)
pony_apply_flags(PonyEngine.Job.Impl TRUE)
pony_add_to_module_list(PonyEngine.Job.Impl PONY_BASE_MODULES)

pony_apply_flags(PonyEngine.Log.Ext TRUE)
pony_apply_flags(PonyEngine.Log.Impl TRUE)
pony_add_to_module_list(PonyEngine.Log.Impl PONY_LOG_MODULES)
pony_apply_flags(PonyEngine.Log.File.Impl TRUE)
pony_add_to_module_list(PonyEngine.Log.File.Impl PONY_LOG_MODULES)

pony_apply_flags(PonyEngine.File TRUE)
pony_apply_flags(PonyEngine.File.Impl TRUE)
pony_add_to_module_list(PonyEngine.File.Impl PONY_PLATFORM_MODULES)

pony_apply_flags(PonyEngine.MessagePump TRUE)
pony_apply_flags(PonyEngine.MessagePump.Impl TRUE)
pony_add_to_module_list(PonyEngine.MessagePump.Impl PONY_PLATFORM_MODULES)

pony_apply_flags(PonyEngine.Surface TRUE)
pony_apply_flags(PonyEngine.Surface.Impl TRUE)
pony_add_to_module_list(PonyEngine.Surface.Impl PONY_PLATFORM_MODULES)

pony_apply_flags(PonyEngine.RawInput TRUE)
pony_apply_flags(PonyEngine.RawInput.Ext TRUE)
pony_apply_flags(PonyEngine.RawInput.Impl TRUE)
pony_add_to_module_list(PonyEngine.RawInput.Impl PONY_INPUT_MODULES)
pony_apply_flags(PonyEngine.RawInput.Keyboard.Impl TRUE)
pony_add_to_module_list(PonyEngine.RawInput.Keyboard.Impl PONY_INPUT_MODULES)
pony_apply_flags(PonyEngine.RawInput.Mouse.Impl TRUE)
pony_add_to_module_list(PonyEngine.RawInput.Mouse.Impl PONY_INPUT_MODULES)
pony_apply_flags(PonyEngine.RawInput.XInput.Impl TRUE)
pony_add_to_module_list(PonyEngine.RawInput.XInput.Impl PONY_INPUT_MODULES)

pony_apply_flags(PonyEngine.RenderDevice TRUE)
pony_apply_flags(PonyEngine.RenderDevice.Ext TRUE)
pony_apply_flags(PonyEngine.RenderDevice.Impl TRUE)
pony_add_to_module_list(PonyEngine.RenderDevice.Impl PONY_RENDER_MODULES)
pony_apply_flags(PonyEngine.RenderDevice.D3D12.Impl TRUE)
pony_add_to_module_list(PonyEngine.RenderDevice.D3D12.Impl PONY_RENDER_MODULES)
pony_apply_flags(PonyEngine.Shader TRUE)

pony_apply_flags(PonyEngine.Resource TRUE)
pony_apply_flags(PonyEngine.Resource.Ext TRUE)
pony_apply_flags(PonyEngine.Resource.Impl TRUE)
pony_add_to_module_list(PonyEngine.Resource.Impl PONY_RESOURCE_MODULES)
pony_apply_flags(PonyEngine.Resource.File.Impl TRUE)
pony_add_to_module_list(PonyEngine.Resource.File.Impl PONY_RESOURCE_MODULES)
pony_apply_flags(PonyEngine.Resource.Pack.Impl TRUE)
pony_add_to_module_list(PonyEngine.Resource.Pack.Impl PONY_RESOURCE_MODULES)

pony_apply_flags(PonyEngine.World TRUE)
pony_apply_flags(PonyEngine.World.Impl TRUE)
pony_add_to_module_list(PonyEngine.World.Impl PONY_LOGIC_MODULES)

if(PONY_ENGINE_ADD_SAMPLE)
	message(VERBOSE "Adding sample")
	add_subdirectory("Samples/${PONY_ENGINE_SAMPLE_NAME}/Sample")
endif()

pony_apply_flags(Sample FALSE)
pony_add_to_module_list(Sample PONY_GAME_MODULES)

set(PONY_INSTALL_TARGETS PonyEngine.Application.Impl)
if(PONY_MAKE_GROUPS)
	message(VERBOSE "Making application module groups")
	pony_manage_module_group(PONY_BASE_MODULES PonyModule.Base TRUE PONY_INSTALL_TARGETS)
	pony_manage_module_group(PONY_LOG_MODULES PonyModule.Log TRUE PONY_INSTALL_TARGETS)
	pony_manage_module_group(PONY_PLATFORM_MODULES PonyModule.Platform TRUE PONY_INSTALL_TARGETS)
	pony_manage_module_group(PONY_INPUT_MODULES PonyModule.Input TRUE PONY_INSTALL_TARGETS)
	pony_manage_module_group(PONY_RENDER_MODULES PonyModule.Render TRUE PONY_INSTALL_TARGETS)
	pony_manage_module_group(PONY_RESOURCE_MODULES PonyModule.Resource TRUE PONY_INSTALL_TARGETS)
	pony_manage_module_group(PONY_LOGIC_MODULES PonyModule.Logic TRUE PONY_INSTALL_TARGETS)
	pony_manage_module_group(PONY_GAME_MODULES PonyModule.Game FALSE PONY_INSTALL_TARGETS)
else()
	message(VERBOSE "Adding application modules")
	pony_add_application_modules(
		${PONY_BASE_MODULES}
		${PONY_LOG_MODULES}
		${PONY_PLATFORM_MODULES}
		${PONY_INPUT_MODULES}
		${PONY_RENDER_MODULES}
		${PONY_RESOURCE_MODULES}
		${PONY_LOGIC_MODULES}
		${PONY_GAME_MODULES}
	)
endif()

message(VERBOSE "Installing")
install(TARGETS ${PONY_INSTALL_TARGETS}
	RUNTIME DESTINATION .
	LIBRARY DESTINATION
)
