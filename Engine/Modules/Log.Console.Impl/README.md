# PonyEngine.Log.Console.Impl module

Logger implementation that logs to a standard console.

## Dependencies

- [PonyEngine.Application](../Application)
- [PonyEngine.Core](../Core)
- [PonyEngine.Log](../Log)
- [PonyEngine.Log.Ext](../Log.Ext)

## CMake variables

These variables are used to configure the build of the module:

| Variable name                   | Default value | Description                                              |
|:--------------------------------|:-------------:|:---------------------------------------------------------|
| `PONY_ENGINE_LOG_CONSOLE_ORDER` | p             | PonyEngine.Log.Console.Impl module initialization order. |

## For Pony Engine developers

The module has a simple implementation:

- [ConsoleLogger](Source/Main-ConsoleLogger.cppm) - console logger;
- [ConsoleLoggerModule](Source/Main-ConsoleLoggerModule.cppm) - console logger module.
