# PonyEngine.WinInput.Impl module

WinAPI input module implementation.

The module requires a platform specific implementation.

## Dependencies

- [PonyEngine.Application](../Application)
- [PonyEngine.Core](../Core)
- [PonyEngine.Log](../Log)
- [PonyEngine.WinInput](../WinInput)
- Windows SDK 10.0.26100.0

## CMake variables

These variables are used to configure the build of the module:

| Variable name                | Default value | Description                                           |
|:-----------------------------|:-------------:|:------------------------------------------------------|
| `PONY_ENGINE_WININPUT_ORDER` | p             | PonyEngine.WinInput.Impl module initialization order. |

## For Pony Engine developers

Main submodules:

- [InputDispatcher](Source/Main-InputDispatcher.cppm) - WinAPI input dispatcher;
- [InputDispatcherModule](Source/Main-InputDispatcherModule.cppm) - WinAPI input dispatcher module.
