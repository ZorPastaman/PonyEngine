# PonyEngine.Application.Impl module for Windows

Platform independent module: [PonyEngine.Application.Impl](../../../Modules/Application.Impl).

The main() function returns an application exit code or -1 on any uncaught exception.

## CMake variables

These variables are used to configure the build of the module:

| Variable name                                         | Default value               | Description                                                                                                                |
|:------------------------------------------------------|:---------------------------:|:---------------------------------------------------------------------------------------------------------------------------|
| `PONY_ENGINE_APPLICATION_MODE`                        | GUI                         | Application mode. Must be Console or GUI.                                                                                  |
| `PONY_ENGINE_CREATE_CONSOLE`                          | OFF                         | Enable console. Can be used only in GUI builds.                                                                            |
| `PONY_ENGINE_APPLICATION_PROCESS_PRIORITY`            | ABOVE_NORMAL_PRIORITY_CLASS | Application process priority. Must be DWORD or predefined priority class.                                                  |
| `PONY_ENGINE_APPLICATION_NEXT_FRAME_BUSY_SPIN_LENGTH` | 0.001                       | Amount of time in seconds that is waited on busy spin. All other time before it is waited on thread sleep. Must be double. |

## CMake functions

| Function name              | Script file                  | Description                              |
|:---------------------------|:-----------------------------|:-----------------------------------------|
| `pony_add_winapi_resource` | [File](CMake/Resource.cmake) | Adds a resource to a generated .rc file. |
| `pony_add_winapi_icon`     | [File](CMake/Resource.cmake) | Adds an icon to a generated .rc file.    |
| `pony_add_winapi_cursor`   | [File](CMake/Resource.cmake) | Adds a cursor to a generated .rc file.   |

## For Pony Engine developers

## C\++ modules

### [PonyEngine.Application.Impl.Windows](Source/Main.cppm)

Main submodules:

#### [ConsoleProcess](Source/Main-ConsoleProcess.cppm)

Console process implementation.

#### [GUIProcess](Source/Main-GUIProcess.cppm)

GUI process implementation.

## [Launch](Source/Launch.cpp)

C\++ main() function.

### Data:

#### [Manifest](Data/Application.manifest.in)

Template for the application manifest. It's used by the CMake script to generate a correct application manifest.
