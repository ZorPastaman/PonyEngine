# PonyEngine.Log.Ext module

Log extension API module. Provides interfaces for the logger extensions.

By default, the engine logger logs only to the console. For additional log outputs, modules must add sub-loggers to the logger.

## Dependencies

- [PonyEngine.Core](../Core)
- [PonyEngine.Log](../Log)
- [PonyEngine.Application.Ext](../Application.Ext)

## C\++ modules

### [PonyEngine.Log.Ext](Source/Public/Main.cppm)

Main sub-modules:

#### [ISubLogger](Source/Public/Main-ISubLogger.cppm)

Sub-logger interface. Each sub-logger that is added to the logger must implement it.

#### [LogEntry](Source/Public/Main-LogEntry.cppm)

Log info that is passed to each sub-logger on a log event.
It contains `LogEntry.formattedMessage` - message formatted by the logger. And in the most cases, it's enough to log it.
But if your sub-logger needs initial info, `LogEntry` contains it as well.

#### [ILoggerContext](Source/Public/Main-ILoggerContext.cppm)

Interface representing the logger context. Provides access to the application context and functions that allow to log to the console.
Sub-loggers may use those functions to log errors, warnings, and other things. It's useful because sub-loggers can't throw.

#### [ILoggerModuleContext](Source/Public/Main-ILoggerModuleContext.cppm)

Interface representing the logger module context. This interface is used by modules to add sub-loggers. It may be accessed via module data after the logger module initialization.

## C\++ headers

### [PonyEngine/Log/Console.h](Include/Public/PonyEngine/Log/Console.h)

Provides helper macros with conditionally compiled code, controlled by the configured log level and stacktrace level defines.
The configuration macros are inherited from [PonyEngine.Log](../Log).

Helpers:

| Define                                                   | Description                                                                          |
|:---------------------------------------------------------|:-------------------------------------------------------------------------------------|
| `PONY_CONSOLE_PUSH(logger, type, message, ...)`          | Pushes the log to a console without a level check.                                   |
| `PONY_CONSOLE_PUSH_X(logger, exception, ...)`            | Pushes the exception log to a console without a level check.                         |
| `PONY_CONSOLE(logger, type, message, ...)`               | Logs the log to a console with a level check.                                        |
| `PONY_CONSOLE_IF(condition, logger, type, message, ...)` | Logs the log to a console with a level check if the `condition` is `true`.           |
| `PONY_CONSOLE_X(logger, exception, ...)`                 | Logs the exception log to a console with a level check.                              |
| `PONY_CONSOLE_X_IF(condition, logger, exception, ...)`   | Logs the exception log to a console with a level check if the `condition` is `true`. |

All the helper macros support string formatting.

```
PonyEngine::Log::ILoggerContext& logger = GetLogger();
int value = 42;
bool condition = false;

PONY_CONSOLE(logger, PonyEngine::Log::LogType::Info, "Info message.");
PONY_CONSOLE(logger, PonyEngine::Log::LogType::Warning, "Unexpected value: {}.", value);
PONY_CONSOLE_IF(condition, logger, PonyEngine::Log::LogType::Info, "Info message.");

PONY_CONSOLE_X(logger, std::current_exception());
PONY_CONSOLE_X(logger, std::current_exception(), "On validating.");
PONY_CONSOLE_X(logger, std::current_exception(), "On validating value: {}.", value);
PONY_CONSOLE_X(condition, logger, std::current_exception(), "On validating value: {}.", value);
```

## Custom sub-logger

How to add a custom sub-logger.

1. Create a class that implements `PonyEngine::Log::ISubLogger`;
2. Create an engine module and add it to the engine application;
3. Set the module initialization order after the logger initialization order;
4. In the module `StartUp()` get `PonyEngine::Log::ILoggerModuleContext`;
5. Add the sub-logger to the logger module context and save the returned `SubLoggerHandle`.

The module must remove its sub-logger on `ShutDown()`:

1. In the module `ShutDown()` get `PonyEngine::Log::ILoggerModuleContext`;
2. Remove the sub-logger using a `SubLoggerHandle` that was returned on adding.

Example:

```
void SubLoggerModule::StartUp(Application::IModuleContext& context)
{
	ILoggerModuleContext* const loggerModuleContext = context.GetData<ILoggerModuleContext>();
	subLoggerHandle = loggerModuleContext->AddSubLogger([&](ILoggerContext& loggerContext)
	{
		return std::make_shared<SubLogger>(loggerContext);
	}
}

void SubLoggerModule::ShutDown(Application::IModuleContext& context)
{
	ILoggerModuleContext* const loggerModuleContext = context.GetData<ILoggerModuleContext>();
	loggerModuleContext->RemoveSubLogger(subLoggerHandle);
}
```
