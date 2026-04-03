# PonyEngine.Log.Impl module

Log implementation module.

## CMake variables

These variables are used to configure the build of the module:

| Variable name           | Default value | Description                                      |
|:------------------------|:-------------:|:-------------------------------------------------|
| `PONY_ENGINE_LOG_ORDER` | p             | PonyEngine.Log.Impl module initialization order. |

## For Pony Engine developers

Main submodules:

- [Logger](Source/Private/Main-Logger.cppm) - logger;
- [LoggerModule](Source/Private/Main-LoggerModule.cppm) - logger module;
- [LogFiller](Source/Private/Main-LogFiller.cppm) - utility functions to make a formatted string.

The [Logger](Source/Private/Main-Logger.cppm) uses `thread_local` strings as formatted string cache to minimize allocations and make logging multithreading-friendly.
The central logging function `Log(const LogEntry& logEntry)` that logs to a console and sub-loggers uses a `lock_guard` to prevent concurrent execution on logging itself.
