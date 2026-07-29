# PonyEngine.Application.Impl module

Application implementation module.

The module requires a platform specific implementation.

## Dependencies

- [PonyEngine.Application](../Application)
- [PonyEngine.Core](../Core)
- [PonyEngine.Log](../Log)

## CMake variables

These variables are used to configure the build of the module:

| Variable name                                 | Default value | Description                                                                                                           |
|:----------------------------------------------|:-------------:|:----------------------------------------------------------------------------------------------------------------------|
| `PONY_ENGINE_APPLICATION_ROOT_PATH`           | ""            | Root path. It must be relative to an executable directory, and the folder must exist at runtime. Empty path is valid. |
| `PONY_ENGINE_APPLICATION_TARGET_FRAME_PERIOD` | 0.0           | Application target frame period in seconds. Must be double.                                                           |
