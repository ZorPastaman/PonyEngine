# PonyEngine.Application.Impl module for Windows

Platform independent module: [PonyEngine.Application.Impl](../../../Modules/Application.Impl).

## CMake variables

These variables are used to configure the build of the module:

| Variable name                  | Default value | Description                                     |
|:-------------------------------|:-------------:|:------------------------------------------------|
| `PONY_ENGINE_APPLICATION_MODE` | "GUI"         | Application mode. Must be Console or GUI.       |
| `PONY_ENGINE_CREATE_CONSOLE`   | OFF           | Enable console. Can be used only in GUI builds. |

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

It returns 0 on success and -1 on any uncaught exception.

### Data:

#### [Manifest](Data/Application.manifest.in)

Template for the application manifest. It's used by the CMake script to generate a correct application manifest.
