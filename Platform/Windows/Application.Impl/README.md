# PonyEngine.Application.Impl module for Windows

Platform independent module: [PonyEngine.Application.Impl](../../../Engine/Application.Impl).

## CMake variables

These variables are used to configure the build of the module:

| Variable name                      | Default value | Description                                                                                                           |
|:-----------------------------------|:-------------:|:----------------------------------------------------------------------------------------------------------------------|
| `PONY_ENGINE_CREATE_CONSOLE`       | OFF           | Enable console.                                                                                                       |
| `PONY_ENGINE_PLATFORM_CONSOLE_LOG` | ON            | Enable logging to the platform console.                                                                               |
| `PONY_ENGINE_ROOT_PATH`            |               | Root path. It must be relative to an executable directory, and the folder must exist at runtime. Empty path is valid. |
| `PONY_APP_ICON`                    |               | Application icon path. Must be .ico file. If it's '<Default>', the engine icon is used.                               |
| `PONY_APP_CURSOR`                  |               | Application cursor path. Must be .cur file. If not set, the Surface module is expected to create a default cursor.    |

## For Pony Engine developers

### Main submodules:

#### [App](Source/Private/Main-App.cppm)

Main application class. Controls the managers and loggers.

#### [AppDataManager](Source/Private/Main-AppDataManager.cppm)

Windows specific application data manager.

#### [LoggerManager](Source/Private/Main-LoggerManager.cppm)

Windows logger manager. On logging to a console, it logs to both a standard C\++ console and Windows console.

#### [PathManager](Source/Private/Main-PathManager.cppm)

Gets and provides application paths.

#### [DefaultLogger](Source/Private/Main-DefaultLogger.cppm)

Default Windows logger.

#### [Console](Source/Private/Main-Console.cppm)

Utilities to control a Windows console.

#### [Process](Source/Private/Main-Process.cppm)

Utilities to control the application process.

### [main()](Source/Main.cpp)

Main function.

### Data:

#### [Manifest](Data/Application.manifest.in)

Template for the application manifest. It's used by the CMake script to generate a correct application manifest.
