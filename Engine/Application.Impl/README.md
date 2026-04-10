# PonyEngine.Application.Impl module

Application implementation module. Implements [PonyEngine.Application.Ext](../Application.Ext).

The module also has `main()` function.

The module requires a platform specific implementation.

## Dependencies

- [PonyEngine.Core](../Core)
- [PonyEngine.Log](../Log)
- [PonyEngine.Application.Ext](../Application.Ext)

## CMake variables

These variables are used to configure the build of the module:

| Variable name                | Default value | Description                                             |
|:-----------------------------|:-------------:|:--------------------------------------------------------|
| `PONY_ENGINE_DEFAULT_LOGGER` | ON            | Enable default logger. It logs everything to a console. |
| `PONY_ENGINE_CONSOLE_LOG`    | ON            | Enable standard C++ console.                            |

## For Pony Engine developers

The module contains a bunch of platform-independent managers. The platform implementation must provide a `main()` function and `IApplicationContext` implementation.
The idea is that the application class is just an orchestrator for different managers. The `main()` function should create the application class and run it.

### Managers:

- [FlowManager](Source/Main-FlowManager.cppm) - has a `Run()` function that controls the main engine flow, knows a current frame and flow state;
- [LoggerManager](Source/Main-LoggerManager.cppm) - knows a current logger and switches them, must be inherited in a platform implementation;
- [ThreadManager](Source/Main-ThreadManager.cppm) - knows a main thread id;
- [ServiceManager](Source/Main-ServiceManager.cppm) - contains and manages services;
- [ModuleManager](Source/Main-ModuleManager.cppm) - initializes and deinitializes modules, must be created after all the managers the services may access.

### Additional sub-modules:

- [ExitCodes](Source/Main-ExitCodes.cppm) - default exit codes;
- [DefaultLogger](Source/Main-DefaultLogger.cppm) - default logger that must be used by the application at initialization, must be inherited in a platform implementation;
- [ConsoleUtility](Source/Main-ConsoleUtility.cppm) - utilities for a standard C\++ console;
- [IdentityUtility](Source/Main-IdentityUtility.cppm) - utilities for a project meta info: names, titles and versions;
- [PathUtility](Source/Main-PathUtility.cppm) - path utilities.
