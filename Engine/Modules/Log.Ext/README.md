# PonyEngine.Log.Ext module

Log extension API module. Provides interfaces for the logger extensions.

By default, the engine logger logs only to the console. For additional log outputs, modules must add sub-loggers to the logger.

## Dependencies

- [PonyEngine.Core](../Core)
- [PonyEngine.Log](../Log)
- [PonyEngine.Application](../Application)

## C\++ modules

### [PonyEngine.Log.Ext](Source/Main.cppm)

Main sub-modules:

#### [ISubLogger](Source/Main-ISubLogger.cppm)

Sub-logger interface. Each sub-logger that is added to the logger must implement it.

#### [LogEntry](Source/Main-LogEntry.cppm)

Log info that is passed to each sub-logger on a log event.
It contains `LogEntry.formattedMessage` - message formatted by the logger. And in the most cases, it's enough to log it.
But if your sub-logger needs initial info, `LogEntry` contains it as well.

#### [ILoggerContext](Source/Main-ILoggerContext.cppm)

Interface representing the logger context. Provides access to the application and functions that allow to log to the console.
Sub-loggers may use those functions to log errors, warnings, and other things. It's useful because sub-loggers can't throw.

#### [ILoggerModuleContext](Source/Main-ILoggerModuleContext.cppm)

Interface representing the logger module context. This interface is used by modules to add sub-loggers. It may be accessed via module data after the logger module initialization.

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
