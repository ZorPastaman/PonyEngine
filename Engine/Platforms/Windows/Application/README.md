# PonyEngine.Application module for Windows

Platform independent module: [PonyEngine.Application](../../../Modules/Application).

## C\++ modules

### [PonyEngine.Application.Windows](Source/Main.cppm)

Main interfaces:

#### [IApplication](Source/Main-IApplication.cppm)

Windows specific application, inherits the platform independent interface. 
The application implementation on Windows must implement this interface.

Users may simply cast platform independent interface to this one via `static_cast`.

This interface exposes Windows-only features: additional `main()` arguments, an application icon and an application cursor.
Only one icon and one cursor can be assigned. Both are optional.
