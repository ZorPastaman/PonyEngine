# Engine build

Pony Engine is very modular. Game developers decide what modules they need and pass required build flags.
To build a game, create your own project, set Pony Engine module variables, add Pony Engine as a dependency and then add your game targets.

## Tools

Some modules or cmake functions require tools built for a host platform. Build them first, and then build the engine and a game.
See [Tools](../Tools) docs for more info.

The folder with tools must be added to the environment.

## Modules

There are two types of modules: feature modules and modification modules. Feature modules add targets while modification modules modify targets added by feature modules.

To configure a module, a specific CMake flag must be `true`.

### Feature modules

| Module name                                                         | Build flag                            |
|:--------------------------------------------------------------------|:--------------------------------------|
| [PonyEngine.Application](Modules/Application)                       | `PONY_ENGINE_APPLICATION`             |
| [PonyEngine.Application.Impl](Modules/Application.Impl)             | `PONY_ENGINE_APPLICATION_IMPL`        |
| [PonyEngine.Core](Modules/Core)                                     | `PONY_ENGINE_CORE`                    |
| [PonyEngine.File](Modules/File)                                     | `PONY_ENGINE_FILE`                    |
| [PonyEngine.File.Impl](Modules/File.Impl)                           | `PONY_ENGINE_FILE_IMPL`               |
| [PonyEngine.Job](Modules/Job)                                       | `PONY_ENGINE_JOB`                     |
| [PonyEngine.Job.Impl](Modules/Job.Impl)                             | `PONY_ENGINE_JOB_IMPL`                |
| [PonyEngine.Log](Modules/Log)                                       | `PONY_ENGINE_LOG`                     |
| [PonyEngine.Log.Ext](Modules/Log.Ext)                               | `PONY_ENGINE_LOG_EXT`                 |
| [PonyEngine.Log.Impl](Modules/Log.Impl)                             | `PONY_ENGINE_LOG_IMPL`                |
| [PonyEngine.Log.Console.Impl](Modules/Log.Console.Impl)             | `PONY_ENGINE_LOG_CONSOLE_IMPL`        |
| [PonyEngine.Log.File.Impl](Modules/Log.File.Impl)                   | `PONY_ENGINE_LOG_FILE_IMPL`           |
| [PonyEngine.Log.WinDebug.Impl](Modules/Log.PConsole.Impl)           | `PONY_ENGINE_LOG_WinDebug_IMPL`       |
| [PonyEngine.RawInput](Modules/RawInput)                             | `PONY_ENGINE_RAW_INPUT`               |
| [PonyEngine.RawInput.Ext](Modules/RawInput.Ext)                     | `PONY_ENGINE_RAW_INPUT_EXT`           |
| [PonyEngine.RawInput.Impl](Modules/RawInput.Impl)                   | `PONY_ENGINE_RAW_INPUT_IMPL`          |
| [PonyEngine.RawInput.Keyboard.Impl](Modules/RawInput.Keyboard.Impl) | `PONY_ENGINE_RAW_INPUT_KEYBOARD_IMPL` |
| [PonyEngine.RawInput.Mouse.Impl](Modules/RawInput.Mouse.Impl)       | `PONY_ENGINE_RAW_INPUT_MOUSE_IMPL`    |
| [PonyEngine.RawInput.XInput.Impl](Modules/RawInput.XInput.Impl)     | `PONY_ENGINE_RAW_INPUT_XINPUT_IMPL`   |
| [PonyEngine.Resource](Modules/Resource)                             | `PONY_ENGINE_RESOURCE`                |
| [PonyEngine.Resource.Ext](Modules/Resource.Ext)                     | `PONY_ENGINE_RESOURCE_EXT`            |
| [PonyEngine.Resource.Impl](Modules/Resource.Impl)                   | `PONY_ENGINE_RESOURCE_IMPL`           |
| [PonyEngine.Resource.Pack](Modules/Resource.Pack)                   | `PONY_ENGINE_RESOURCE_PACK`           |
| [PonyEngine.Resource.Pack.Impl](Modules/Resource.Pack.Impl)         | `PONY_ENGINE_RESOURCE_PACK_IMPL`      |
| [PonyEngine.Time](Modules/Time)                                     | `PONY_ENGINE_TIME`                    |
| [PonyEngine.Time.Impl](Modules/Time.Impl)                           | `PONY_ENGINE_TIME_IMPL`               |
| [PonyEngine.WinInput](Modules/WinInput)                             | `PONY_ENGINE_WININPUT`                |
| [PonyEngine.WinInput.Impl](Modules/WinInput.Impl)                   | `PONY_ENGINE_WININPUT_IMPL`           |
| [PonyEngine.World](Modules/World)                                   | `PONY_ENGINE_WORLD`                   |
| [PonyEngine.World.Impl](Modules/World.Impl)                         | `PONY_ENGINE_WORLD_IMPL`              |

Some modules may require modifications to work because they need implementation for a specific platform or a compiler or due to other things.

### Modification modules

| Module name                                                                       | Build flag                                   |
|:----------------------------------------------------------------------------------|:---------------------------------------------|
| [PonyEngine.Application.WinAPI](Modules/Application.WinAPI)                       | `PONY_ENGINE_APPLICATION_WINAPI`             |
| [PonyEngine.Application.Impl.WinAPI](Modules/Application.Impl.WinAPI)             | `PONY_ENGINE_APPLICATION_IMPL_WINAPI`        |
| [PonyEngine.Core.MSVC](Modules/Core.MSVC)                                         | `PONY_ENGINE_CORE_MSVC`                      |
| [PonyEngine.Core.WinAPI](Modules/Core.WinAPI)                                     | `PONY_ENGINE_CORE_WINAPI`                    |
| [PonyEngine.File.Impl.WinAPI](Modules/File.Impl.WinAPI)                           | `PONY_ENGINE_FILE_IMPL_WINAPI`               |
| [PonyEngine.RawInput.Keyboard.Impl.WinAPI](Modules/RawInput.Keyboard.Impl.WinAPI) | `PONY_ENGINE_RAW_INPUT_KEYBOARD_IMPL_WINAPI` |
| [PonyEngine.RawInput.Mouse.Impl.WinAPI](Modules/RawInput.Mouse.Impl.WinAPI)       | `PONY_ENGINE_RAW_INPUT_MOUSE_IMPL_WINAPI`    |

If the variable `PONY_ENGINE_AUTO_SELECT_PLATFORM_MODULES` is ON, the engine will select platform modification modules automatically.

Supported platforms:

- Windows

If the variable `PONY_ENGINE_AUTO_SELECT_COMPILER_MODULES` is ON, the engine will select compiler modification modules automatically.

Supported compilers:

- MSVC

### Application module linking

The engine does not automatically link application modules—including its own. This is intentional, giving the game developers full control over the build configuration.

To link an application module, explicitly add it in your CMake scripts: `target_link_libraries(PonyEngine.Application.Impl PRIVATE <MyModule>)` where `<MyModule>` can be either a game module or an engine module (for example, `PonyEngine.RawInput.Impl`).

If you use a default application implementation module, you can also use a shortcut like this: `pony_add_application_modules(<Application module list>)`.

Only implementation modules need to be linked.

### Module grouping

By default, all engine modules are built as static libraries. This allows the entire engine and game to be linked into a single executable, which is ideal for release builds.

For debug builds, however, shared libraries are often preferable due to faster iteration and build times. To support this, the engine provides a CMake function `pony_make_module_group`, which combines one or more static libraries into a shared library.

When using this approach, link the resulting shared library to the application instead of the original static modules.

See [PonyEngine.Core docs](Modules/Core) for details.

### Custom application modules

The engine allows adding custom game modules to the application. These modules are then executed as part of the application lifecycle.

See the [Application docs](Modules/Application) for details.

If the modules do not need to be referenced by the engine application, no special setup is required.

### Modules parameters

By default, the engine modules don't have compile and link flags. Users must set them manually. Example: `target_compile_options(PonyEngine.Core PRIVATE /fp:fast)`, `target_link_options(PonyEngine.Core PRIVATE /LTCG)`

Also, by default, the engine modules don't have log defines. Users must set them manually. Example: `pony_set_log_defines(PonyEngine.Application.Impl "Warning" "Error")`. See the [PonyEngine.Log docs](Modules/Log) for details.

## Text

The engine exclusively uses char and std::string with UTF-8 encoding, except where platform APIs require different types or encodings.

## Build

The build system is based entirely on CMake. To build a game, simply add the engine as a CMake dependency.

### import std;

The engine requires C\++23 and makes extensive use of C\++ modules, including the `std` module. Therefore, the `std` module must be built before building the engine.
This can be done either manually or via CMake. However, CMake support for automatically building the `std` module is still experimental. To enable it, set `CMAKE_EXPERIMENTAL_CXX_IMPORT_STD` to the value corresponding to your CMake version.
Refer to the CMake documentation for the correct value: https://github.com/Kitware/CMake/blob/v3.31.0/Help/dev/experimental.rst - change the version in the link to your CMake version.

The `std` module must be compiled with flags compatible with the rest of the project. When building it via CMake, these flags should be set using `add_compile_options()` **before** the first `project()` call.
If some targets require different compile options, you can reset them using: `set_directory_properties(PROPERTIES COMPILE_OPTIONS "")`.

### Compile flags

The engine modules must be compiled with `RTTI` and exceptions enabled.

### CMake variables

#### Input

Input parameters for the engine CMake scripts. These variables are initialized with default values in the CMake cache but can be overridden before configuration.

| Variable name                | Default value      | Description                                                                                                                      |
|:-----------------------------|:------------------:|:---------------------------------------------------------------------------------------------------------------------------------|
| `PONY_COMPANY_NAME`          | "PonyEngine"       | Company name. It's used to create project folders. So, it must be a valid directory name.                                        |
| `PONY_PROJECT_NAME`          | "PonyEngineGame"   | Project name. It's used to create project folders. So, it must be a valid directory name. It's also used for an executable name. |
| `PONY_PROJECT_VERSION_MAJOR` | 0                  | Project major version.                                                                                                           |
| `PONY_PROJECT_VERSION_MINOR` | 0                  | Project minor version.                                                                                                           |
| `PONY_PROJECT_VERSION_PATCH` | 0                  | Project patch version.                                                                                                           |
| `PONY_PROJECT_VERSION_TWEAK` | 0                  | Project tweak version.                                                                                                           |
| `PONY_COMPANY_TITLE`         | "Pony Engine"      | Company title. It's used in GUI only. May be any non-empty string.                                                               |
| `PONY_PROJECT_TITLE`         | "Pony Engine Game" | Project title. It's used in GUI only. May be any non-empty string.                                                               |

### CMake functions

The engine has some useful CMake functions:

| Function name                                   | Script file                  | Description                                             |
|:------------------------------------------------|:-----------------------------|:--------------------------------------------------------|
| `pony_validate_path`                            | [File](CMake/Path.cmake)     | Validates if the path variable is correct.              |
| `pony_validate_name`                            | [File](CMake/Project.cmake)  | Validates if the name variable is correct.              |
| `pony_validate_title`                           | [File](CMake/Project.cmake)  | Validates if the title variable is correct.             |
| `pony_validate_version`                         | [File](CMake/Project.cmake)  | Validates if the version variable is correct.           |

Some modules may add their own functions. Refer to their documentation to find out.
