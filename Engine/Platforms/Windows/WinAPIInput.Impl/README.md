# PonyEngine.WinAPIInput.Impl module for Windows

Platform independent module: [PonyEngine.WinAPIInput.Impl](../../../Modules/WinAPIInput.Impl).

## Dependencies

- [PonyEngine.Application](../Application)
- [PonyEngine.Core](../Core)
- [PonyEngine.Log](../../../Modules/Log)

## CMake variables

These variables are used to configure the build of the module:

| Variable name                    | Default value | Description                                              |
|:---------------------------------|:-------------:|:---------------------------------------------------------|
| `PONY_ENGINE_WINAPI_INPUT_ORDER` | p             | PonyEngine.WinAPIInput.Impl module initialization order. |

## For Pony Engine developers

Main submodules:

- [InputDispatcher](Source/Main-InputDispatcher.cppm) - WinAPI input dispatcher;
- [InputDispatcherModule](Source/Main-InputDispatcherModule.cppm) - WinAPI input dispatcher module.
