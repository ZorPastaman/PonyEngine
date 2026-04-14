# Pony Engine
Pony Engine is a modular game engine with a minimal core. Users can easily add their own modules and even replace the engine modules.

## Key features

- Modular architecture;
- Replaceable engine modules;
- Easily extensible;
- Mesh shader–based render.

## Prerequisites

- CMake 3.31+;
- Ninja generator;
- C\++ 23 compiler;
- HLSL SM 6.6+ compiler;
- Platform SDKs.

## Quick start for game developers

### Simple way

1. Download any sample project from [here](Game);
2. Follow instructions of the chosen sample.

### Advanced way

1. Build C++ std module;
2. Add the engine as a dependency to your CMake project. Add this to your project `CMakeLists.txt`:
```
FetchContent_Declare(
	PonyEngine
	GIT_REPOSITORY https://github.com/ZorPastaman/PonyEngine.git
	GIT_TAG <Branch_or_Tag>
)
FetchContent_MakeAvailable(PonyEngine)
```
3. Add your game modules (see [Architecture](#Architecture) and [Modules](#modules) for details);
4. Link the engine and game modules to the engine application module. 
5. Build and install the project.

## Architecture

The engine core is intentionally minimal. Most functionality is implemented in separate modules. Users control which modules are included at build time using CMake, and they can add their own modules easily.
Some modules are split into API and implementation parts. This allows replacing implementations without breaking dependencies, since modules depend only on APIs, not concrete implementations.

There are these module types:

| Module type    | Name suffix | Description                                                                                                                  |
|:---------------|:------------|:-----------------------------------------------------------------------------------------------------------------------------|
| Utility        | -           | Modules that contain utility functions and classes. They may be referenced by any other module.                              |
| API            | -           | Modules that contain service interfaces. They also may contain some utilities. They may be referenced by any other module.   |
| Implementation | .Impl       | Modules that contain implementations of service and extension interfaces. They are not referenced directly by other modules. |
| Extension API  | .Ext        | Modules that contain interfaces for extensions of implementation modules. They also may contain some utilities.              |

The engine runtime is built around services.
Modules register services in a global application context, and the application ticks them every frame.
Services interact with each other via interfaces only.
See more in the [Application.Ext](Engine/Application.Ext) readme.

The key idea behind cross-service interaction is strict separation of interfaces and implementations.
Services communicate only through interfaces, while implementations live in separate modules.
This allows replacing implementation modules without affecting other parts of the engine.

Some implementation modules support extensions.
For example, an input module provides core functionality but does not include support for specific devices.
Device support is added via extension modules that implement the corresponding extension interfaces.

## Modules

Each module is a separate CMake target. A module name is its target name in CMake scripts as well.

### Core modules

These modules are always added to a build.

| Module name                                            | Description                                                                                                        |
|:-------------------------------------------------------|:-------------------------------------------------------------------------------------------------------------------|
| [PonyEngine.Core](Engine/Core)                         | Core utilities module: Math, Hash, Meta, Memory, Serialization and Type utilities.                                 |
| [PonyEngine.Log](Engine/Log)                           | Logging API module.                                                                                                |
| [PonyEngine.Application.Ext](Engine/Application.Ext)   | Application extension API module. Provides interfaces access to engine services, logging, and application context. |
| [PonyEngine.Application.Impl](Engine/Application.Impl) | Application implementation module. Contains `main()` and a default logger as well.                                 |

### Optional modules

These modules are optional. To add them to a build, a specific CMake flag must be `true`.

| Module name                                                                    | Build flag                                  | Description                                                                                                                   |
|:-------------------------------------------------------------------------------|:--------------------------------------------|:------------------------------------------------------------------------------------------------------------------------------|
| [PonyEngine.Log.Ext](Engine/Log.Ext)                                           | `PONY_ENGINE_LOG_EXT`                       | Logger extension API module. Provides interfaces for the logger extensions.                                                   |
| [PonyEngine.Log.Impl](Engine/Log.Impl)                                         | `PONY_ENGINE_LOG_IMPL`                      | Logger module. Replaces the default logger. Logs to a console and sub-loggers that are added as extensions.                   |
| [PonyEngine.Log.File.Impl](Engine/Log.File.Impl)                               | `PONY_ENGINE_LOG_FILE_IMPL`                 | File sub-logger module. That sub-logger logs to a log file.                                                                   |
| [PonyEngine.Time](Engine/Time)                                                 | `PONY_ENGINE_TIME`                          | Time service API module. The service provides info about delta time, fixed time step and other time info.                     |
| [PonyEngine.Time.Impl](Engine/Time.Impl)                                       | `PONY_ENGINE_TIME_IMPL`                     | Time service implementation module.                                                                                           |
| [PonyEngine.MessagePump](Engine/MessagePump)                                   | `PONY_ENGINE_MESSAGE_PUMP`                  | Message pump service API module. The service reads platform messages and provides info about them.                            |
| [PonyEngine.MessagePump.Impl](Engine/MessagePump.Impl)                         | `PONY_ENGINE_MESSAGE_PUMP_IMPL`             | Message pump service implementation module.                                                                                   |
| [PonyEngine.Surface](Engine/Surface)                                           | `PONY_ENGINE_SURFACE`                       | Surface service API module. The service controls an output video surface.                                                     |
| [PonyEngine.Surface.Impl](Engine/Surface.Impl)                                 | `PONY_ENGINE_SURFACE_IMPL`                  | Surface service implementation module.                                                                                        |
| [PonyEngine.RawInput](Engine/RawInput)                                         | `PONY_ENGINE_RAW_INPUT`                     | Raw input service API module. The service provides input from different devices via input providers.                          |
| [PonyEngine.RawInput.Ext](Engine/RawInput.Ext)                                 | `PONY_ENGINE_RAW_INPUT_EXT`                 | Raw input service extension API module. Provides interfaces for input providers that implement support for different devices. |
| [PonyEngine.RawInput.Impl](Engine/RawInput.Impl)                               | `PONY_ENGINE_RAW_INPUT_IMPL`                | Raw input service implementation module. Gets input from input providers that are added as extensions.                        |
| [PonyEngine.RawInput.Keyboard.Impl](Engine/RawInput.Keyboard.Impl)             | `PONY_ENGINE_RAW_INPUT_KEYBOARD_IMPL`       | Raw input keyboard provider module. Reads input from keyboard devices and provides it to a raw input service.                 |
| [PonyEngine.RawInput.Mouse.Impl](Engine/RawInput.Mouse.Impl)                   | `PONY_ENGINE_RAW_INPUT_MOUSE_IMPL`          | Raw input mouse provider module. Reads input from mouse devices and provides it to a raw input service.                       |
| [PonyEngine.RawInput.XInput.Impl](Engine/RawInput.XInput.Impl)                 | `PONY_ENGINE_RAW_INPUT_XINPUT_IMPL`         | Raw input XInput provider module. Reads input from XInput devices and provides it to a raw input service.                     |
| [PonyEngine.Shader](Engine/Shader)                                             | `PONY_ENGINE_SHADER`                        | Shader utilities module. Provides utility functions and classes for both C\++ and hlsl.                                        |
| [PonyEngine.RenderDevice](Engine/RenderDevice)                                 | `PONY_ENGINE_RENDER_DEVICE`                 | Render device service API module. The service provides a low level access to a GPU.                                           |
| [PonyEngine.RenderDevice.Ext](Engine/RenderDevice.Ext)                         | `PONY_ENGINE_RENDER_DEVICE_EXT`             | Render device service extension API module. Provides interfaces for backends.                                                 |
| [PonyEngine.RenderDevice.Impl](Engine/RenderDevice.Impl)                       | `PONY_ENGINE_RENDER_DEVICE_IMPL`            | Render device service implementation module. Provides a low level access to a GPU via added backends.                         |
| [PonyEngine.RenderDevice.Direct3D12.Impl](Engine/RenderDevice.Direct3D12.Impl) | `PONY_ENGINE_RENDER_DEVICE_DIRECT3D12_IMPL` | Direct3D12 backend implementation.                                                                                            |

### Platform modules

Platform support is configured via CMake scripts. These scripts adjust the build by selecting implementations, adding platform-specific code, and configuring existing modules.
Some modules are completely platform-independent. Others require platform-specific implementations, while some can optionally provide a platform-specific behavior.

Supported platforms:

- [Windows](Platform/Windows)

The table of the module-platform compatibility:

| Module name                                                                    | Requires platform implementation | [Windows](Platform/Windows) |
|:-------------------------------------------------------------------------------|:--------------------------------:|:---------------------------:|
| [PonyEngine.Core](Engine/Core)                                                 | -                                | &check;                     |
| [PonyEngine.Application.Ext](Engine/Application.Ext)                           | -                                | &check;                     |
| [PonyEngine.Application.Impl](Engine/Application.Impl)                         | &check;                          | &check;                     |
| [PonyEngine.Log](Engine/Log)                                                   | -                                | &check;                     |
| [PonyEngine.Log.Ext](Engine/Log.Ext)                                           | -                                | &check;                     |
| [PonyEngine.Log.Impl](Engine/Log.Impl)                                         | -                                | &check;                     |
| [PonyEngine.Log.File.Impl](Engine/Log.File.Impl)                               | -                                | &check;                     |
| [PonyEngine.Time](Engine/Time)                                                 | -                                | &check;                     |
| [PonyEngine.Time.Impl](Engine/Time.Impl)                                       | -                                | &check;                     |
| [PonyEngine.MessagePump](Engine/MessagePump)                                   | -                                | &check;                     |
| [PonyEngine.MessagePump.Impl](Engine/MessagePump.Impl)                         | &check;                          | &check;                     |
| [PonyEngine.Surface](Engine/Surface)                                           | -                                | &check;                     |
| [PonyEngine.Surface.Impl](Engine/Surface.Impl)                                 | &check;                          | &check;                     |
| [PonyEngine.RawInput](Engine/RawInput)                                         | -                                | &check;                     |
| [PonyEngine.RawInput.Ext](Engine/RawInput.Ext)                                 | -                                | &check;                     |
| [PonyEngine.RawInput.Impl](Engine/RawInput.Impl)                               | -                                | &check;                     |
| [PonyEngine.RawInput.Keyboard.Impl](Engine/RawInput.Keyboard.Impl)             | &check;                          | &check;                     |
| [PonyEngine.RawInput.Mouse.Impl](Engine/RawInput.Mouse.Impl)                   | &check;                          | &check;                     |
| [PonyEngine.RawInput.XInput.Impl](Engine/RawInput.XInput.Impl)                 | &check;                          | &check;                     |
| [PonyEngine.Shader](Engine/Shader)                                             | -                                | &check;                     |
| [PonyEngine.RenderDevice](Engine/RenderDevice)                                 | -                                | &check;                     |
| [PonyEngine.RenderDevice.Ext](Engine/RenderDevice.Ext)                         | -                                | &check;                     |
| [PonyEngine.RenderDevice.Impl](Engine/RenderDevice.Impl)                       | -                                | &check;                     |
| [PonyEngine.RenderDevice.Direct3D12.Impl](Engine/RenderDevice.Direct3D12.Impl) | &check;                          | &check;                     |

The engine automatically applies platform-specific configuration based on `CMAKE_SYSTEM_NAME`. The value must match one of the supported platforms.
Users can provide their own platform implementations by setting the CMake flag `PONY_ENGINE_CUSTOM_PLATFORM` to `true`. In this case, the built-in platform configuration is disabled, and users are responsible for configuring the modules themselves.

### Compiler modules

Unfortunately, some functions are not implemented in the C++ standard and require to use compiler specific operations.
The only module that needs them is [PonyEngine.Core](Engine/Core). See its readme for details.

Supported compilers:

- [MSVC](Compiler/MSVC)

The engine automatically applies compiler-specific configuration based on CMake compiler variables. The compiler must be supported.
Users can provide their own compiler implementations by setting CMake flag `PONY_ENGINE_CUSTOM_COMPILER` to `true`. In this case, the built-in compiler configuration is disabled, and users are responsible for configuring the modules themselves.

### Application module linking

The engine does not automatically link application modules—including its own. This is intentional, giving the game developers full control over the build configuration.

To link an application module, explicitly add it in your CMake scripts: `target_link_libraries(PonyEngine.Application.Impl PRIVATE <MyModule>)` where `<MyModule>` can be either a game module or an engine module (for example, `PonyEngine.RawInput.Impl`).

Only implementation modules need to be linked.

### Module grouping

By default, all engine modules are built as static libraries. This allows the entire engine and game to be linked into a single executable, which is ideal for release builds.

For debug builds, however, shared libraries are often preferable due to faster iteration and build times. To support this, the engine provides a CMake function `pony_make_module_group`, which combines one or more static libraries into a shared library.

When using this approach, link the resulting shared library to the application instead of the original static modules.

See [PonyEngine.Core docs](Engine/Core) for details.

### Custom application modules

The engine allows adding custom game modules to the application. These modules are then executed as part of the application lifecycle.

See the [Application.Ext docs](Engine/Application.Ext) for details.

If the modules do not need to be referenced by the engine application, no special setup is required.

### Essential examples

These are the main examples of how to configure a project to build a game on Pony Engine with built-in and custom modules:

- [ModuleSample](Game/ModuleSample) - how to build a custom module;
- [ApplicationServiceSample](Game/ApplicationServiceSample) - how to build a custom module that adds a service.

### Modules parameters

By default, the engine modules don't have compile and link flags. Users must set them manually. Example: `target_compile_options(PonyEngine.Core PRIVATE /fp:fast)`, `target_link_options(PonyEngine.Core PRIVATE /LTCG)`

Also, by default, the engine modules don't have log defines. Users must set them manually. Example: `pony_set_log_defines(PonyEngine.Application.Impl "Warning" "Error)`. See the [PonyEngine.Log docs](Engine/Log) for details.

## Math

The engine uses a left-handed coordinate system where X is right, Y is up, and Z is forward. The rotation order is ZXY (roll-pitch-yaw). The matrices are column-major.
The surfaces like windows and textures use a coordinate system where X is right, and Y is down.

## Render

The engine render modules are mesh-shader based. The traditional render pipeline isn't supported.
Only HLSL shaders are currently supported.

Because the engine supports different render APIs, some features of HLSL are limited.
The register types are shared and not divided into `b, t, u, s`. The engine treats spaces as descriptor set indices. The normal indices are treated as indices.

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

##### Icon

There are 3 modes to set the application icon:

1. `PONY_APP_ICON_MODE` = any CMake false constant. The application will not have an icon at all;
2. `PONY_APP_ICON_MODE` = `Default`. The application will use the engine icon.
3. `PONY_APP_ICON_MODE` = `Custom`. The application will use a custom icon.

#### Output

Output parameters are passed via `PARENT_SCOPE` to a CMake script that called the engine CMake script.

| Variable name               | Description                                   |
|:----------------------------|:----------------------------------------------|
| `PONY_ENGINE_NAME`          | Pony Engine name. It's always "PonyEngine".   |
| `PONY_ENGINE_VERSION_MAJOR` | Pony Engine major version.                    |
| `PONY_ENGINE_VERSION_MINOR` | Pony Engine minor version.                    |
| `PONY_ENGINE_VERSION_PATCH` | Pony Engine patch version.                    |
| `PONY_ENGINE_VERSION_TWEAK` | Pony Engine tweak version.                    |
| `PONY_ENGINE_VERSION`       | Pony Engine version.                          |
| `PONY_ENGINE_TITLE`         | Pony Engine title. It's always "Pony Engine". |

### CMake functions

The engine has some useful CMake functions:

| Function name             | Script file                 | Description                                   |
|:--------------------------|:----------------------------|:----------------------------------------------|
| `pony_validate_path`      | [File](CMake/Path.cmake)    | Validates if the path variable is correct.    |
| `pony_validate_name`      | [File](CMake/Project.cmake) | Validates if the name variable is correct.    |
| `pony_validate_title`     | [File](CMake/Project.cmake) | Validates if the title variable is correct.   |
| `pony_validate_version`   | [File](CMake/Project.cmake) | Validates if the version variable is correct. |
| `compile_shader_with_dxc` | [File](CMake/Shader.cmake)  | Compiles a shader using DXC compiler.         |

Some modules may add their own functions. Refer to their documentation to find out.

## Logo

The engine logo can be found [here](Logo). It contains the logo source and logo variants for all the supported platforms.

## License

This repo is licensed under the [MIT License](LICENSE.md).

### Custom licenses

Some folders contain files with their own licenses.
Each such folder has its own LICENSE file.
That license applies to the contents of that folder and all its subfolders.

List of custom licenses:

- The engine logo is licensed under the [CC BY 4.0 License](Logo/LICENSE.md).
- Third party libraries. Check [ThirdParty](ThirdParty.md) for a full list.

When in doubt, always check for a LICENSE file inside a folder before using its content.

## For Pony Engine developers

This section is intended for Pony Engine developers and developers of its forks. Game developers who just use the engine may stop reading this readme here.

### Presets

The repo uses CMake presets to control build pipelines. The presets are chosen based on the target platform, compiler, and engine build type.
The engine build type determines `CMAKE_BUILD_TYPE`, engine optimization level, game optimization level, engine log level, game log level, and some other flags.

Presets use different toolchains for each platform–compiler combination. The toolchains must set required variables, compile and link flags, and provide functions to control them.
Each toolchain must define `PONY_COMPILE_FLAGS_DEBUG`, `PONY_COMPILE_FLAGS_RELEASE`, `PONY_LINK_FLAGS_DEBUG`, and `PONY_LINK_FLAGS_RELEASE`, and include [Compiler.cmake](CMake/Toolchains/Compiler.cmake).

#### Windows MSVC toolchain

The toolchain for the Windows–MSVC combination requires presetting some environment variables for a correct build using vcvars*.bat.
Refer to Microsoft documentation: https://learn.microsoft.com/en-us/cpp/build/building-on-the-command-line?view=msvc-170 for details.

### Tests

The repo uses Catch2 for unit tests with CMake integration. See the [Tests](Tests) section to find the tests.

The repo uses Catch2 benchmark tools as well. The benchmarks are compiled and run only if the `PONY_ENGINE_TESTING_BENCHMARK` define is set to `true`.

### Games

The engine testing can be easier if you build one of game samples to the engine build.
To add it, set `PONY_ENGINE_ADD_GAME` CMake variable to `true` and `PONY_ENGINE_GAME_NAME` to a name of game sample.
The presets already have them.
