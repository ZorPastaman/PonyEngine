# PonyEngine.Log.PlatformConsole.Impl module

Logger implementation that logs to a platform console.

## Dependencies

- [PonyEngine.Application](../Application)
- [PonyEngine.Core](../Core)
- [PonyEngine.Log](../Log)
- [PonyEngine.Log.Ext](../Log.Ext)

## CMake variables

These variables are used to configure the build of the module:

| Variable name                             | Default value | Description                                                      |
|:------------------------------------------|:-------------:|:-----------------------------------------------------------------|
| `PONY_ENGINE_LOG_PLATFORM_CONSOLE_ORDER` | p             | PonyEngine.Log.PlatformConsole.Impl module initialization order. |

## For Pony Engine developers

The module has a simple implementation:

- [PlatformConsoleLogger](Source/Main-PlatformConsoleLogger.cppm) - platform console logger;
- [PlatformConsoleLoggerModule](Source/Main-PlatformConsoleLoggerModule.cppm) - platform console logger module.
