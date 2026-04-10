# PonyEngine.Log module

Log API module. Provides interfaces for logging.

## Dependencies

- [PonyEngine.Core](../Core)

## C\++ modules

### [PonyEngine.Log](Source/Main.cppm)

Main sub-modules:

#### [ILogger](Source/Main-ILogger.cppm)

Logger interface. It has functions to log messages and exceptions.

#### [LogType](Source/Main-LogType.cppm)

Log types (from lowest to highest level):

- Verbose
- Debug
- Info
- Warning
- Error
- Exception

## C\++ headers

### [PonyEngine/Log/Log.h](Include/Public/PonyEngine/Log/Log.h)

Provides helper macros with conditionally compiled code, controlled by the configured log level and stacktrace level defines.

Control defines:

| Define                          | Description                                     |
|:--------------------------------|:------------------------------------------------|
| `PONY_LOG_VERBOSE`              | If defined, verbose logs are compiled.          |
| `PONY_LOG_DEBUG`                | If defined, debug logs are compiled.            |
| `PONY_LOG_INFO`                 | If defined, info logs are compiled.             |
| `PONY_LOG_WARNING`              | If defined, warning logs are compiled.          |
| `PONY_LOG_ERROR`                | If defined, error logs are compiled.            |
| `PONY_LOG_EXCEPTION`            | If defined, exception logs are compiled.        |
| `PONY_LOG_STACKTRACE_VERBOSE`   | If defined, verbose logs include stacktraces.   |
| `PONY_LOG_STACKTRACE_DEBUG`     | If defined, debug logs include stacktraces.     |
| `PONY_LOG_STACKTRACE_INFO`      | If defined, info logs include stacktraces.      |
| `PONY_LOG_STACKTRACE_WARNING`   | If defined, warning logs include stacktraces.   |
| `PONY_LOG_STACKTRACE_ERROR`     | If defined, error logs include stacktraces.     |
| `PONY_LOG_STACKTRACE_EXCEPTION` | If defined, exception logs include stacktraces. |

These defines must be set individually in each CMake target.

Helpers:

| Define                                               | Description                                                             |
|:-----------------------------------------------------|:------------------------------------------------------------------------|
| `PONY_LOG_PUSH(logger, type, message, ...)`          | Pushes the log without a level check.                                   |
| `PONY_LOG_PUSH_X(logger, exception, ...)`            | Pushes the exception log without a level check.                         |
| `PONY_LOG(logger, type, message, ...)`               | Logs the log with a level check.                                        |
| `PONY_LOG_IF(condition, logger, type, message, ...)` | Logs the log with a level check if the `condition` is `true`.           |
| `PONY_LOG_X(logger, exception, ...)`                 | Logs the exception log with a level check.                              |
| `PONY_LOG_X_IF(condition, logger, exception, ...)`   | Logs the exception log with a level check if the `condition` is `true`. |

All the helper macros support string formatting.

Examples:

```
PonyEngine::Application::IApplication* application = GetEngineApplication();
int value = 42;
bool condition = false;

PONY_LOG(application->Logger(), PonyEngine::Log::LogType::Info, "Info message.");
PONY_LOG(application->Logger(), PonyEngine::Log::LogType::Warning, "Unexpected value: {}.", value);
PONY_LOG_IF(condition, application->Logger(), PonyEngine::Log::LogType::Info, "Info message.");

PONY_LOG_X(application->Logger(), std::current_exception());
PONY_LOG_X(application->Logger(), std::current_exception(), "On validating.");
PONY_LOG_X(application->Logger(), std::current_exception(), "On validating value: {}.", value);
PONY_LOG_X(condition, application->Logger(), std::current_exception(), "On validating value: {}.", value);
```

## CMake functions

| Function name          | Script file              | Description                                  |
|:-----------------------|:-------------------------|:---------------------------------------------|
| `pony_set_log_defines` | [File](CMake/Log.cmake)  | Sets log and stacktrace defines to a target. |
