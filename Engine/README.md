# Engine build

Pony Engine is very modular. Game developers decide what modules they need and pass required build flags.
To build a game, create your own project, set Pony Engine module variables, add Pony Engine as a dependency and then add your game targets.

## Tools

Some modules or cmake functions require tools built for a host platform. Build them first, and then build the engine and a game.
See [Tools](../Tools) docs for more info.

Path to built tools must be assigned to `PONY_TOOLS_INSTALL_DIR`.

## Modules

Each module is a separate CMake target. A module name is its target name in CMake scripts as well.

To a module to a build, a specific CMake flag must be `true`.

| Module name                                                           | Build flag                             | Description                                                                                                                   |
|:----------------------------------------------------------------------|:---------------------------------------|:------------------------------------------------------------------------------------------------------------------------------|
| [PonyEngine.Application](Modules/Application)                         | `PONY_ENGINE_APPLICATION`              | Application API module. Provides interfaces to access main engine info, to register interfaces and tickables.                 |
| [PonyEngine.Application.Impl](Modules/Application.Impl)               | `PONY_ENGINE_APPLICATION_IMPL`         | Application implementation module. Contains `main()` and a default logger as well.                                            |
| [PonyEngine.Core](Modules/Core)                                       | `PONY_ENGINE_CORE`                     | Core utilities module: Math, Hash, Meta, Memory and Type utilities.                                                           |
| [PonyEngine.File](Modules/File)                                       | `PONY_ENGINE_FILE`                     | File service API module. The file service is a simple way to utilize modern SSDs with totally async read/write operations.    |
| [PonyEngine.File.Impl](Modules/File.Impl)                             | `PONY_ENGINE_FILE_IMPL`                | File service implementation module.                                                                                           |
| [PonyEngine.Job](Modules/Job)                                         | `PONY_ENGINE_JOB`                      | Job service API module. The job service is a simple way to utilize multi-threaded CPUs.                                       |
| [PonyEngine.Job.Impl](Modules/Job.Impl)                               | `PONY_ENGINE_JOB_IMPL`                 | Job service implementation module.                                                                                            |
| [PonyEngine.Log](Modules/Log)                                         | `PONY_ENGINE_LOG`                      | Logging API module.                                                                                                           |
| [PonyEngine.Log.Ext](Modules/Log.Ext)                                 | `PONY_ENGINE_LOG_EXT`                  | Logger extension API module. Provides interfaces for the logger extensions.                                                   |
| [PonyEngine.Log.Impl](Modules/Log.Impl)                               | `PONY_ENGINE_LOG_IMPL`                 | Logger module. Replaces the default logger. Logs to a console and sub-loggers that are added as extensions.                   |
| [PonyEngine.Log.Console.Impl](Modules/Log.Console.Impl)               | `PONY_ENGINE_LOG_CONSOLE_IMPL`         | Logger implementation that logs to a standard console.                                                                        |
| [PonyEngine.Log.File.Impl](Modules/Log.File.Impl)                     | `PONY_ENGINE_LOG_FILE_IMPL`            | File sub-logger module. That sub-logger logs to a log file.                                                                   |
| [PonyEngine.Log.PConsole.Impl](Modules/Log.PConsole.Impl)             | `PONY_ENGINE_LOG_PCONSOLE_IMPL`        | Logger implementation that logs to a platform console.                                                                        |
| [PonyEngine.RawInput](Modules/RawInput)                               | `PONY_ENGINE_RAW_INPUT`                | Raw input service API module. The service provides input from different devices via input providers.                          |
| [PonyEngine.RawInput.Ext](Modules/RawInput.Ext)                       | `PONY_ENGINE_RAW_INPUT_EXT`            | Raw input service extension API module. Provides interfaces for input providers that implement support for different devices. |
| [PonyEngine.RawInput.Impl](Modules/RawInput.Impl)                     | `PONY_ENGINE_RAW_INPUT_IMPL`           | Raw input service implementation module. Gets input from input providers that are added as extensions.                        |
| [PonyEngine.RawInput.Keyboard.Impl](Modules/RawInput.Keyboard.Impl)   | `PONY_ENGINE_RAW_INPUT_KEYBOARD_IMPL`  | Raw input keyboard provider module. Reads input from keyboard devices and provides it to a raw input service.                 |
| [PonyEngine.RawInput.Mouse.Impl](Modules/RawInput.Mouse.Impl)         | `PONY_ENGINE_RAW_INPUT_MOUSE_IMPL`     | Raw input mouse provider module. Reads input from mouse devices and provides it to a raw input service.                       |
| [PonyEngine.RawInput.XInput.Impl](Modules/RawInput.XInput.Impl)       | `PONY_ENGINE_RAW_INPUT_XINPUT_IMPL`    | Raw input XInput provider module. Reads input from XInput devices and provides it to a raw input service.                     |
| [PonyEngine.RenderDevice](Modules/RenderDevice)                       | `PONY_ENGINE_RENDER_DEVICE`            | Render device service API module. The service provides a low level access to a GPU.                                           |
| [PonyEngine.RenderDevice.Ext](Modules/RenderDevice.Ext)               | `PONY_ENGINE_RENDER_DEVICE_EXT`        | Render device service extension API module. Provides interfaces for backends.                                                 |
| [PonyEngine.RenderDevice.Impl](Modules/RenderDevice.Impl)             | `PONY_ENGINE_RENDER_DEVICE_IMPL`       | Render device service implementation module. Provides a low level access to a GPU via added backends.                         |
| [PonyEngine.RenderDevice.D3D12.Impl](Modules/RenderDevice.D3D12.Impl) | `PONY_ENGINE_RENDER_DEVICE_D3D12_IMPL` | Direct3D12 backend implementation.                                                                                            |
| [PonyEngine.Resource](Modules/Resource)                               | `PONY_ENGINE_RESOURCE`                 | Resource service API module. The service provides resources.                                                                  |
| [PonyEngine.Resource.Ext](Modules/Resource.Ext)                       | `PONY_ENGINE_RESOURCE_EXT`             | Resource service extension API module. Provides interfaces for resource providers.                                            |
| [PonyEngine.Resource.Impl](Modules/Resource.Impl)                     | `PONY_ENGINE_RESOURCE_IMPL`            | Resource service implementation module.                                                                                       |
| [PonyEngine.Resource.Pack](Modules/Resource.Pack)                     | `PONY_ENGINE_RESOURCE_PACK`            | Pack resource provider module API.                                                                                            |
| [PonyEngine.Resource.Pack.Impl](Modules/Resource.Pack.Impl)           | `PONY_ENGINE_RESOURCE_PACK_IMPL`       | Pack resource provider module.                                                                                                |
| [PonyEngine.Shader](Modules/Shader)                                   | `PONY_ENGINE_SHADER`                   | Shader utilities module. Provides utility functions and classes for both C\++ and hlsl.                                       |
| [PonyEngine.Surface](Modules/Surface)                                 | `PONY_ENGINE_SURFACE`                  | Surface service API module. The service controls an output video surface.                                                     |
| [PonyEngine.Surface.Impl](Modules/Surface.Impl)                       | `PONY_ENGINE_SURFACE_IMPL`             | Surface service implementation module.                                                                                        |
| [PonyEngine.Time](Modules/Time)                                       | `PONY_ENGINE_TIME`                     | Time service API module. The service provides info about delta time, fixed time step and other time info.                     |
| [PonyEngine.Time.Impl](Modules/Time.Impl)                             | `PONY_ENGINE_TIME_IMPL`                | Time service implementation module.                                                                                           |
| [PonyEngine.WinAPIInput](Modules/WinAPIInput)                         | `PONY_ENGINE_WINAPI_INPUT`             | The module provides interfaces to register for WinAPI raw input events.                                                       |
| [PonyEngine.WinAPIInput.Impl](Modules/WinAPIInput.Impl)               | `PONY_ENGINE_WINAPI_INPUT_IMPL`        | WinAPI input module implementation.                                                                                           |
| [PonyEngine.World](Modules/World)                                     | `PONY_ENGINE_WORLD`                    | World service API module. The service manages game worlds.                                                                    |
| [PonyEngine.World.Impl](Modules/World.Impl)                           | `PONY_ENGINE_WORLD_IMPL`               | World service implementation module.                                                                                          |

### Platform modules

Platform support is configured via CMake scripts. These scripts adjust the build by selecting implementations, adding platform-specific code, and configuring existing modules.
Some modules are completely platform-independent. Others require platform-specific implementations, while some can optionally provide a platform-specific behavior.

Supported platforms:

- [Windows](Platforms/Windows)

The table of the module-platform compatibility:

| Module name                                                           | Requires platform implementation | [Windows](Platforms/Windows) |
|:----------------------------------------------------------------------|:--------------------------------:|:----------------------------:|
| [PonyEngine.Application](Modules/Application)                         | -                                | &check;                      |
| [PonyEngine.Application.Impl](Modules/Application.Impl)               | &check;                          | &check;                      |
| [PonyEngine.Core](Modules/Core)                                       | -                                | &check;                      |
| [PonyEngine.File](Modules/File)                                       | -                                | &check;                      |
| [PonyEngine.File.Impl](Modules/File.Impl)                             | &check;                          | &check;                      |
| [PonyEngine.Job](Modules/Job)                                         | -                                | &check;                      |
| [PonyEngine.Job.Impl](Modules/Job.Impl)                               | -                                | &check;                      |
| [PonyEngine.Log](Modules/Log)                                         | -                                | &check;                      |
| [PonyEngine.Log.Ext](Modules/Log.Ext)                                 | -                                | &check;                      |
| [PonyEngine.Log.Impl](Modules/Log.Impl)                               | -                                | &check;                      |
| [PonyEngine.Log.Console.Impl](Modules/Log.Console.Impl)               | -                                | &check;                      |
| [PonyEngine.Log.File.Impl](Modules/Log.File.Impl)                     | -                                | &check;                      |
| [PonyEngine.Log.PConsole.Impl](Modules/Log.PConsole.Impl)             | &check;                          | &check;                      |
| [PonyEngine.RawInput](Modules/RawInput)                               | -                                | &check;                      |
| [PonyEngine.RawInput.Ext](Modules/RawInput.Ext)                       | -                                | &check;                      |
| [PonyEngine.RawInput.Impl](Modules/RawInput.Impl)                     | -                                | &check;                      |
| [PonyEngine.RawInput.Keyboard.Impl](Modules/RawInput.Keyboard.Impl)   | &check;                          | &check;                      |
| [PonyEngine.RawInput.Mouse.Impl](Modules/RawInput.Mouse.Impl)         | &check;                          | &check;                      |
| [PonyEngine.RawInput.XInput.Impl](Modules/RawInput.XInput.Impl)       | &check;                          | &check;                      |
| [PonyEngine.RenderDevice](Modules/RenderDevice)                       | -                                | &check;                      |
| [PonyEngine.RenderDevice.Ext](Modules/RenderDevice.Ext)               | -                                | &check;                      |
| [PonyEngine.RenderDevice.Impl](Modules/RenderDevice.Impl)             | -                                | &check;                      |
| [PonyEngine.RenderDevice.D3D12.Impl](Modules/RenderDevice.D3D12.Impl) | &check;                          | &check;                      |
| [PonyEngine.Resource](Modules/Resource)                               | -                                | &check;                      |
| [PonyEngine.Resource.Ext](Modules/Resource.Ext)                       | -                                | &check;                      |
| [PonyEngine.Resource.Impl](Modules/Resource.Impl)                     | -                                | &check;                      |
| [PonyEngine.Resource.Pack](Modules/Resource.Pack)                     | -                                | &check;                      |
| [PonyEngine.Resource.Pack.Impl](Modules/Resource.Pack.Impl)           | -                                | &check;                      |
| [PonyEngine.Shader](Modules/Shader)                                   | -                                | &check;                      |
| [PonyEngine.Surface](Modules/Surface)                                 | -                                | &check;                      |
| [PonyEngine.Surface.Impl](Modules/Surface.Impl)                       | &check;                          | &check;                      |
| [PonyEngine.Time](Modules/Time)                                       | -                                | &check;                      |
| [PonyEngine.Time.Impl](Modules/Time.Impl)                             | -                                | &check;                      |
| [PonyEngine.WinAPIInput](Modules/WinAPIInput)                         | &check;                          | &check;                      |
| [PonyEngine.WinAPIInput.Impl](Modules/WinAPIInput.Impl)               | &check;                          | &check;                      |
| [PonyEngine.World](Modules/World)                                     | -                                | &check;                      |
| [PonyEngine.World.Impl](Modules/World.Impl)                           | -                                | &check;                      |

The engine automatically applies platform-specific configuration based on `CMAKE_SYSTEM_NAME`. The value must match one of the supported platforms.
Users can provide their own platform implementations by setting the CMake flag `PONY_ENGINE_CUSTOM_PLATFORM` to `true`. In this case, the built-in platform configuration is disabled, and users are responsible for configuring the modules themselves.

### Compiler modules

Unfortunately, some functions are not implemented in the C++ standard and require to use compiler specific operations.
That's why the engine build must start with a target `PonyCompiler` and it must contain `PonyCompiler.h` which contains all the required defines:

- `PONY_DLL_EXPORT` - translates to compiler dll export attribute if `PONY_DLL` is defined, empty otherwise.
- `PONY_PRESERVE(symbol)` - preserves the symbol. The symbol is a string.
- `PONY_SECTION_DELIMITER` - returns a section delimiter that is set between a section name and an order.
- `PONY_SECTION(name)` - declares a section with the given name.
- `PONY_ALLOCATE(segment)` - allocates a segment.

Supported compilers:

- [MSVC](Compilers/MSVC)

The engine automatically applies compiler-specific configuration based on CMake compiler variables. The compiler must be supported.
Users can provide their own compiler implementations by setting CMake flag `PONY_ENGINE_CUSTOM_COMPILER` to `true`. In this case, the built-in compiler configuration is disabled, and users are responsible for configuring the modules themselves.
The compiler module must be configured before the engine configuration.

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
| `pony_create_file_resource_manifest`            | [File](CMake/Resource.cmake) | Creates a file resource manifest.                       |
| `pony_add_to_file_resource_manifest`            | [File](CMake/Resource.cmake) | Adds resources to a file resource manifest.             |
| `pony_remove_from_file_resource_manifest`       | [File](CMake/Resource.cmake) | Removes resources from a file resource manifest.        |
| `pony_upgrade_file_resource_manifest`           | [File](CMake/Resource.cmake) | Upgrades a file resource manifest to an actual version. |
| `pony_make_resource_for_file_resource_manifest` | [File](CMake/Resource.cmake) | Makes a resource string for a file resource manifest.   |
| `pony_compile_file_resource_manifest`           | [File](CMake/Resource.cmake) | Compiles a file resource manifest.                      |
| `pony_create_pack_resource_manifest`            | [File](CMake/Resource.cmake) | Creates a pack resource manifest.                       |
| `pony_add_to_pack_resource_manifest`            | [File](CMake/Resource.cmake) | Adds resources to a pack resource manifest.             |
| `pony_remove_from_pack_resource_manifest`       | [File](CMake/Resource.cmake) | Removes resources from a pack resource manifest.        |
| `pony_upgrade_pack_resource_manifest`           | [File](CMake/Resource.cmake) | Upgrades a pack resource manifest to an actual version. |
| `pony_make_resource_for_pack_resource_manifest` | [File](CMake/Resource.cmake) | Makes a resource string for a pack resource manifest.   |
| `pony_compile_pack_resource_manifest`           | [File](CMake/Resource.cmake) | Compiles a pack resource manifest.                      |
| `pony_compile_shader_with_dxc`                  | [File](CMake/Shader.cmake)   | Compiles a shader using DXC compiler.                   |

Some modules may add their own functions. Refer to their documentation to find out.
