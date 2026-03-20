# Pony Engine
Pony Engine is a modular game engine with a minimal core. Users can easily add their own modules and even replace the engine modules.

## Prerequisites

- CMake 3.31+;
- C++ 23 compiler;
- HLSL SM 6.6+ compiler;
- Platform SDKs.

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

### Core modules

These modules are always added to a build.

| Module name                                            | Description                                                                                              |
|:-------------------------------------------------------|:---------------------------------------------------------------------------------------------------------|
| [PonyEngine.Core](Engine/Core)                         | Core utilities module: Math, Hash, Meta, Memory, Serialization and Type utilities.                       |
| [PonyEngine.Log](Engine/Log)                           | Logging API module.                                                                                      |
| [PonyEngine.Application.Ext](Engine/Application.Ext)   | Application extension API module. Provides access to engine services, logging, and application metadata. |
| [PonyEngine.Application.Impl](Engine/Application.Impl) | Application implementation module. Contains `main()` and a default logger as well.                       |

### Optional modules

These modules are optional. To add them to a build, a specific CMake flag must be `true`.

| Module name                                                                    | Build flag                                  | Description                                                                                                                   |
|:-------------------------------------------------------------------------------|:--------------------------------------------|:------------------------------------------------------------------------------------------------------------------------------|
| [PonyEngine.Log.Ext](Engine/Log.Ext)                                           | `PONY_ENGINE_LOG_EXT`                       | Logger extension API module. Provides a sub-logger interface.                                                                 |
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
| [PonyEngine.Shader](Engine/Shader)                                             | `PONY_ENGINE_SHADER`                        | Shader utilities module. Provides utility functions and classes for both c++ and hlsl.                                        |
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

## Math

The engine uses a left-handed coordinate system where X is right, Y is up, and Z is forward. The rotation order is ZXY (roll-pitch-yaw). The matrices are column-major.
The surfaces like windows and textures use a coordinate system where X is right, and Y is down.

## Render

The engine render modules are mesh-shader based. The traditional render pipeline isn't supported.
Only HLSL shaders are currently supported.

## Text

The engine exclusively uses char and std::string with UTF-8 encoding, except where platform APIs require different types or encodings.

## License

This project is licensed under the [MIT License](LICENSE.md).

### Custom licenses

Some folders contain files with their own licenses.
Each such folder has its own LICENSE file.
That license applies to the contents of that folder and all its subfolders.

List of custom licenses:

- The engine logo is licensed under the [CC BY 4.0 License](Logo/LICENSE.md).
- Third party libraries. Check [ThirdParty](ThirdParty.md) for a full list.

When in doubt, always check for a LICENSE file inside a folder before using its content.
