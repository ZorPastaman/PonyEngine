# PonyEngine.Log.Ext feature module

Log extension API module. Provides interfaces for loggers that can be added to a log hub.

Adds `PonyEngine.Log.Ext` target as a static library.

## Dependencies

- [PonyEngine.Core](../Core)
- [PonyEngine.Log](../Log)

## C\++ modules

### [PonyEngine.Log.Ext](Source/Main.cppm)

Main sub-modules:

#### [LogEntry](Source/Main-LogEntry.cppm)

Log info that is passed to each logger on a log event.
It contains different data of a log request.

#### [ILogger](Source/Main-ILogger.cppm)

Object that logs data to different outputs.

#### [ILogHub](Source/Main-ILogHub.cppm)

Object that receives log requests and sends them to registered loggers. All the loggers must be added to it.
