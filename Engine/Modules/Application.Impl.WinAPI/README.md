# PonyEngine.Application.Impl.WinAPI modification module

Adds WinAPI application support to [PonyEngine.Application.Impl](../Application.Impl).

The main() function returns an application exit code or -1 on any uncaught exception.

Modifies `PonyEngine.Application.Impl` target.

## Dependencies

- [PonyEngine.Application.WinAPI](../Application.WinAPI)
- [PonyEngine.Application.Impl](../Application.Impl)
- [PonyEngine.Core.WinAPI](../Core.WinAPI)
- Windows SDK 10.0.26100.0

## CMake variables

These variables are used to configure the build of the module:

| Variable name                                         | Default value                        | Description                                                                                                                |
|:------------------------------------------------------|:------------------------------------:|:---------------------------------------------------------------------------------------------------------------------------|
| `PONY_ENGINE_APPLICATION_MODE`                        | GUI                                  | Application mode. Must be Console or GUI.                                                                                  |
| `PONY_ENGINE_APPLICATION_CREATE_CONSOLE`              | OFF                                  | Enable console. Can be used only in GUI builds.                                                                            |
| `PONY_ENGINE_APPLICATION_PROCESS_PRIORITY`            | ABOVE_NORMAL_PRIORITY_CLASS          | Application process priority. Must be DWORD or predefined priority class.                                                  |
| `PONY_ENGINE_APPLICATION_NEXT_FRAME_BUSY_SPIN_LENGTH` | 0.001                                | Amount of time in seconds that is waited on busy spin. All other time before it is waited on thread sleep. Must be double. |
| `PONY_ENGINE_APPLICATION_SET_DEFAULT_THREAD_ROLES`    | ON                                   | If true, the default thread roles are added automatically.                                                                 |
| `PONY_ENGINE_APPLICATION_MAIN_THREAD_ROLE`            | Main                                 | Main thread role. If empty or false, no role is applied.                                                                   |
| `PONY_ENGINE_APPLICATION_ADD_DEFAULT_MANIFEST`        | ON                                   | Add default manifest.                                                                                                      |
| `PONY_ENGINE_APPLICATION_SUPPORTED_OS`                | 8e0f7a12-bfb3-4fe8-b9a5-48fd50a15a9a | Supported OS GUID. By default, it corresponds to Windows 10/11.                                                               |

## CMake functions

| Function name              | Script file                    | Description                              |
|:---------------------------|:-------------------------------|:-----------------------------------------|
| `pony_add_winapi_resource` | [File](CMake/Resource.cmake)   | Adds a resource to a generated .rc file. |
| `pony_add_winapi_icon`     | [File](CMake/Resource.cmake)   | Adds an icon to a generated .rc file.    |
| `pony_add_winapi_cursor`   | [File](CMake/Resource.cmake)   | Adds a cursor to a generated .rc file.   |
| `pony_add_thread_role`     | [File](CMake/ThreadRole.cmake) | Adds a thread role.                      |

## For Pony Engine developers

## C\++ modules

### [PonyEngine.Application.Impl.Windows](Source/Application.cppm)

#### [ConsoleProcess](Source/Application-ConsoleProcess.cppm)

Console process implementation.

#### [GUIProcess](Source/Application-GUIProcess.cppm)

GUI process implementation.

## [Launch.Console](Source/Launch.Console.cpp)

C\++ main() function for a console application.

## [Launch.GUI](Source/Launch.GUI.cpp)

C\++ main() function for a GUI application.

### Data:

#### [Manifest](Data/Application.manifest.in)

Template for the application manifest. It's used by the CMake script to generate a correct application manifest.
