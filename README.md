# Pony Engine
Pony Engine is a modular game engine with a minimal core. Users can easily add their own modules and even replace the engine modules.

![Logo](Logo/Logo.png)

## Key features

- Modular architecture;
- Replaceable engine modules;
- Easily extensible;
- Mesh shader–based render;
- ECS.

## Prerequisites

- CMake 3.31+;
- Ninja generator;
- C\++ 23 compiler;
- HLSL SM 6.6+ compiler;
- Platform SDKs.

## Quick start for game developers

### Simple way

TODO: reference samples

### Advanced way

#### Build tools (build for a host platform)

1. Build c++ std module;
2. Add the engine tools as a dependency to your CMake project. Add this to your project `CMakeLists.txt`:
```
set(PONY_BUILD_MODE "Tools")
FetchContent_Declare(
	PonyEngineTools
	GIT_REPOSITORY https://github.com/ZorPastaman/PonyEngine.git
	GIT_TAG <Branch_or_Tag>
)
FetchContent_MakeAvailable(PonyEngineTools)
```
3. Add your game build tools if needed;
4. Build and install the tools project.

#### Build runtime (build for a target platform)

1. Build C++ std module;
2. Set a path to the build tools:
```
set(PONY_TOOLS_INSTALL_DIR <path_to_tools>)
```
3. Add the engine runtime as a dependency to your CMake project. Add this to your project `CMakeLists.txt`:
```
set(PONY_BUILD_MODE "Runtime")
FetchContent_Declare(
	PonyEngine
	GIT_REPOSITORY https://github.com/ZorPastaman/PonyEngine.git
	GIT_TAG <Branch_or_Tag>
)
FetchContent_MakeAvailable(PonyEngine)
```
4. Add your game modules (see [Architecture](#Architecture) and [Engine](Engine) for details);
5. Link the engine and game modules to the engine application module. 
6. Build and install the project.

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
Modules register services in a global application, and the application ticks them every frame.
Services interact with each other via interfaces only.
See more in the [Application](Modules/Application) readme.

The key idea behind cross-service interaction is strict separation of interfaces and implementations.
Services communicate only through interfaces, while implementations live in separate modules.
This allows replacing implementation modules without affecting other parts of the engine.

Some implementation modules support extensions.
For example, an input module provides core functionality but does not include support for specific devices.
Device support is added via extension modules that implement the corresponding extension interfaces.

## Custom formats

The engine uses custom file formats for different purposes. You can find their descriptions [here](EngineFormats).

## Build

This repo can be built in different modes. You have to set `PONY_BUILD_MODE` to one of the supported modes:

| Build mode        | Description                                                                                                             |
|:------------------|:------------------------------------------------------------------------------------------------------------------------|
| [Runtime](Engine) | Only runtime part of the engine is built. It's used to build a game as well.                                            |
| [Tools](Tools)    | Different build tools are built. Contains resource compilers and other tools that may be needed for Runtime build mode. |
| [Editor](Editor)  | Engine editor is built. Not yet implemented!                                                                            |

### Output

In any mode, output parameters are passed via `PARENT_SCOPE` to a CMake script that called the engine CMake script.

| Variable name               | Description                                   |
|:----------------------------|:----------------------------------------------|
| `PONY_ENGINE_NAME`          | Pony Engine name. It's always "PonyEngine".   |
| `PONY_ENGINE_VERSION_MAJOR` | Pony Engine major version.                    |
| `PONY_ENGINE_VERSION_MINOR` | Pony Engine minor version.                    |
| `PONY_ENGINE_VERSION_PATCH` | Pony Engine patch version.                    |
| `PONY_ENGINE_VERSION_TWEAK` | Pony Engine tweak version.                    |
| `PONY_ENGINE_VERSION`       | Pony Engine version.                          |
| `PONY_ENGINE_TITLE`         | Pony Engine title. It's always "Pony Engine". |

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
The engine build type determines `CMAKE_BUILD_TYPE`, engine optimization level, engine log level and some other flags.

#### Windows MSVC toolchain

The toolchain for the Windows–MSVC combination requires presetting some environment variables for a correct build using vcvars*.bat.
Refer to Microsoft documentation: https://learn.microsoft.com/en-us/cpp/build/building-on-the-command-line?view=msvc-170 for details.

### Tests

The repo uses Catch2 for unit tests with CMake integration. See the [Tests](Tests) section to find the tests.

The repo uses Catch2 benchmark tools as well. The benchmarks are compiled and run only if the `PONY_ENGINE_TESTING_BENCHMARK` define is set to `true`.
