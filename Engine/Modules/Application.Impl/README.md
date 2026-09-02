# PonyEngine.Application.Impl module

Application implementation module.

Adds `PonyEngine.Application.Impl` target as an executable.

The module requires a platform specific implementation. 
The implementation must have a main() function and provide a context to the app.

## Dependencies

- [PonyEngine.Application](../Application)
- [PonyEngine.Core](../Core)
- [PonyEngine.Log](../Log)

## CMake variables

These variables are used to configure the build of the module:

| Variable name                                 | Default value | Description                                                                                                           |
|:----------------------------------------------|:-------------:|:----------------------------------------------------------------------------------------------------------------------|
| `PONY_ENGINE_APPLICATION_ROOT_PATH`           | ""            | Root path. It must be relative to an executable directory, and the folder must exist at runtime. Empty path is valid. |
| `PONY_ENGINE_APPLICATION_TARGET_FRAME_PERIOD` | 0.002         | Application target frame period in seconds. Must be double.                                                           |

## For Pony Engine developers

### [PonyEngine.Application.Impl](Source/Application.cppm)

#### [App](Source/Application-App.cppm)

Implements `IApplication`. It must be controlled by a platform specific process.
