# PonyEngine.Log.WinDebug.Impl feature module

Logger implementation that logs to a `OutputDebugString()`.

The module requires WinAPI support.

Adds `PonyEngine.Log.WinDebug.Impl` target as a static library.

## Dependencies

- [PonyEngine.Application](../Application)
- [PonyEngine.Core](../Core)
- [PonyEngine.Log](../Log)
- [PonyEngine.Log.Ext](../Log.Ext)
- Windows SDK 10.0.26100.0

## CMake variables

These variables are used to configure the build of the module:

| Variable name                    | Default value | Description                                               |
|:---------------------------------|:-------------:|:----------------------------------------------------------|
| `PONY_ENGINE_LOG_WINDEBUG_ORDER` | p             | PonyEngine.Log.WinDebug.Impl module initialization order. |

## For Pony Engine developers

The module has a simple implementation:

- [WinDebugLogger](Source/WinDebug-WinDebugLogger.cppm) - WinDebug logger;
- [WinDebugLoggerModule](Source/WinDebug-WinDebugLoggerModule.cppm) - WinDebug logger module.

