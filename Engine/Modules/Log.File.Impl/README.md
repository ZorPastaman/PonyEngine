# PonyEngine.Log.File.Impl feature module

Logger implementation that logs to a standard console.

The log file is created in a local data folder. If a file with the same name exists, it will be renamed to `<file_name>_prev.<file_extension>`.

Adds `PonyEngine.Log.File.Impl` target as a static library.

## Dependencies

- [PonyEngine.Application](../Application)
- [PonyEngine.Core](../Core)
- [PonyEngine.Log](../Log)
- [PonyEngine.Log.Ext](../Log.Ext)

## CMake variables

These variables are used to configure the build of the module:

| Variable name                | Default value | Description                                                                                   |
|:-----------------------------|:-------------:|:----------------------------------------------------------------------------------------------|
| `PONY_ENGINE_LOG_FILE_ORDER` | p             | PonyEngine.Log.File.Impl module initialization order.                                         |
| `PONY_ENGINE_LOG_FILE_PATH`  | Logs/Log.log  | Log file path. It must be a relative path. The log file will be created in local data folder. |

## For Pony Engine developers

The module has a simple implementation:

- [FileLogger](Source/File-FileLogger.cppm) - file logger;
- [FileLoggerModule](Source/File-FileLoggerModule.cppm) - file logger module.
