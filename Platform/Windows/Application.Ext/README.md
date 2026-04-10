# PonyEngine.Application.Ext module for Windows

Platform independent module: [PonyEngine.Application.Ext](../../../Engine/Application.Ext).

## C\++ modules

### [PonyEngine.Application.Ext.Windows](Source/Main.cppm)

Main interfaces:

#### [IApplicationContext](Source/Main-IApplicationContext.cppm)

Windows specific application context, inherits the platform independent interface. 
The application context implementation on Windows must implement this interface.

Users may simply cast platform independent interface to this one via `static_cast`.

This interface exposes Windows-only features: additional `main()` arguments, an application icon and an application cursor.
Only one icon and one cursor can be assigned. Both are optional.
