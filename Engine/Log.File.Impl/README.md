# PonyEngine.Log.File.Impl module

Sub-logger implementation module. The sub-logger logs to a log file.

The log file is created in a local data folder. If a file with the same name exists, it will be renamed to `<file_name>_prev.<file_extension>`.

## Dependencies

- [PonyEngine.Core](../Core)
- [PonyEngine.Log](../Log)
- [PonyEngine.Log.Ext](../Log.Ext)
- [PonyEngine.Application.Ext](../Application.Ext)

## CMake variables

These variables are used to configure the build of the module:

| Variable name                | Default value | Description                                                                                   |
|:-----------------------------|:-------------:|:----------------------------------------------------------------------------------------------|
| `PONY_ENGINE_LOG_FILE_ORDER` | p             | PonyEngine.Log.File.Impl module initialization order.                                         |
| `PONY_ENGINE_LOG_FILE_PATH`  | Logs/Log.log  | Log file path. It must be a relative path. The log file will be created in local data folder. |

## For Pony Engine developers

The module has a simple implementation:

- [FileSubLogger](Source/Private/Main-FileSubLogger.cppm) - sub-logger;
- [FileSubLoggerModule](Source/Private/Main-FileSubLoggerModule.cppm) - sub-logger module.
