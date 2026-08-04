function(pony_apply_flags target)
	if(TARGET ${target})
		pony_set_log_defines(${target} ${PONY_ENGINE_LOG_LEVEL} ${PONY_ENGINE_LOG_STACKTRACE_LEVEL})
	endif()
endfunction()

macro(pony_add_to_module_list target module_list)
	if(TARGET ${target})
		list(APPEND ${module_list} ${target})
	endif()
endmacro()

macro(pony_manage_module_group module_list group_target intall_targets)
	if(${module_list})
		pony_make_module_group(${group_target} MODULES ${${module_list}})
		pony_apply_flags(${group_target})
		pony_add_application_modules(${group_target})
		list(APPEND ${intall_targets} ${group_target})
	endif()
endmacro()

if(NOT TARGET PonyEngine.Application.Impl)
	message(FATAL_ERROR "PonyEngine.Application.Impl wasn't added to the engine build")
endif()

set(PONY_LOG_MODULES "")
set(PONY_BASE_MODULES "")
set(PONY_RESOURCE_MODULES "")
set(PONY_RENDER_MODULES "")
set(PONY_INPUT_MODULES "")
set(PONY_LOGIC_MODULES "")

pony_apply_flags(PonyEngine.Core)

pony_apply_flags(PonyEngine.Log)
pony_apply_flags(PonyEngine.Log.Ext)
pony_apply_flags(PonyEngine.Log.Impl)
pony_add_to_module_list(PonyEngine.Log.Impl PONY_LOG_MODULES)
pony_apply_flags(PonyEngine.Log.Console.Impl)
pony_add_to_module_list(PonyEngine.Log.Console.Impl PONY_LOG_MODULES)
pony_apply_flags(PonyEngine.Log.PConsole.Impl)
pony_add_to_module_list(PonyEngine.Log.PConsole.Impl PONY_LOG_MODULES)
pony_apply_flags(PonyEngine.Log.File.Impl)
pony_add_to_module_list(PonyEngine.Log.File.Impl PONY_LOG_MODULES)

pony_apply_flags(PonyEngine.Time)
pony_apply_flags(PonyEngine.Time.Impl)
pony_add_to_module_list(PonyEngine.Time.Impl PONY_BASE_MODULES)
pony_apply_flags(PonyEngine.Job)
pony_apply_flags(PonyEngine.Job.Impl)
pony_add_to_module_list(PonyEngine.Job.Impl PONY_BASE_MODULES)

pony_apply_flags(PonyEngine.File)
pony_apply_flags(PonyEngine.File.Impl)
pony_add_to_module_list(PonyEngine.File.Impl PONY_RESOURCE_MODULES)
pony_apply_flags(PonyEngine.Resource)
pony_apply_flags(PonyEngine.Resource.Ext)
pony_apply_flags(PonyEngine.Resource.Impl)
pony_add_to_module_list(PonyEngine.Resource.Impl PONY_RESOURCE_MODULES)
pony_apply_flags(PonyEngine.Resource.File.Impl)
pony_add_to_module_list(PonyEngine.Resource.File.Impl PONY_RESOURCE_MODULES)
pony_apply_flags(PonyEngine.Resource.Pack.Impl)
pony_add_to_module_list(PonyEngine.Resource.Pack.Impl PONY_RESOURCE_MODULES)

pony_apply_flags(PonyEngine.Surface)
pony_apply_flags(PonyEngine.Surface.Impl)
pony_add_to_module_list(PonyEngine.Surface.Impl PONY_RENDER_MODULES)
pony_apply_flags(PonyEngine.RenderDevice)
pony_apply_flags(PonyEngine.RenderDevice.Ext)
pony_apply_flags(PonyEngine.RenderDevice.Impl)
pony_add_to_module_list(PonyEngine.RenderDevice.Impl PONY_RENDER_MODULES)
pony_apply_flags(PonyEngine.RenderDevice.D3D12.Impl)
pony_add_to_module_list(PonyEngine.RenderDevice.D3D12.Impl PONY_RENDER_MODULES)
pony_apply_flags(PonyEngine.Shader)

pony_apply_flags(PonyEngine.WinAPIInput)
pony_apply_flags(PonyEngine.WinAPIInput.Impl)
pony_add_to_module_list(PonyEngine.WinAPIInput.Impl PONY_INPUT_MODULES)
pony_apply_flags(PonyEngine.RawInput)
pony_apply_flags(PonyEngine.RawInput.Ext)
pony_apply_flags(PonyEngine.RawInput.Impl)
pony_add_to_module_list(PonyEngine.RawInput.Impl PONY_INPUT_MODULES)
pony_apply_flags(PonyEngine.RawInput.Keyboard.Impl)
pony_add_to_module_list(PonyEngine.RawInput.Keyboard.Impl PONY_INPUT_MODULES)
pony_apply_flags(PonyEngine.RawInput.Mouse.Impl)
pony_add_to_module_list(PonyEngine.RawInput.Mouse.Impl PONY_INPUT_MODULES)
pony_apply_flags(PonyEngine.RawInput.XInput.Impl)
pony_add_to_module_list(PonyEngine.RawInput.XInput.Impl PONY_INPUT_MODULES)

pony_apply_flags(PonyEngine.World)
pony_apply_flags(PonyEngine.World.Impl)
pony_add_to_module_list(PonyEngine.World.Impl PONY_LOGIC_MODULES)

pony_apply_flags(PonyEngine.Application)
pony_apply_flags(PonyEngine.Application.Impl)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	include("CMake/EngineModulePostConfigurationWindows.cmake")
endif()

set(PONY_INSTALL_TARGETS PonyEngine.Application.Impl)
if(PONY_MAKE_GROUPS)
	pony_manage_module_group(PONY_LOG_MODULES PonyModule.Log PONY_INSTALL_TARGETS)
	pony_manage_module_group(PONY_BASE_MODULES PonyModule.Base PONY_INSTALL_TARGETS)
	pony_manage_module_group(PONY_INPUT_MODULES PonyModule.Input PONY_INSTALL_TARGETS)
	pony_manage_module_group(PONY_RENDER_MODULES PonyModule.Render PONY_INSTALL_TARGETS)
	pony_manage_module_group(PONY_RESOURCE_MODULES PonyModule.Resource PONY_INSTALL_TARGETS)
	pony_manage_module_group(PONY_LOGIC_MODULES PonyModule.Logic PONY_INSTALL_TARGETS)
else()
	pony_add_application_modules(
		${PONY_LOG_MODULES}
		${PONY_BASE_MODULES}
		${PONY_INPUT_MODULES}
		${PONY_RENDER_MODULES}
		${PONY_RESOURCE_MODULES}
		${PONY_LOGIC_MODULES}
	)
endif()

install(TARGETS ${PONY_INSTALL_TARGETS}
	RUNTIME DESTINATION .
	LIBRARY DESTINATION
)
