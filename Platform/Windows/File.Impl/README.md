# PonyEngine.File.Impl module for Windows

Platform independent module: [PonyEngine.File.Impl](../../../Engine/File.Impl).

## Dependencies

- [PonyEngine.Core](../Core)
- [PonyEngine.Log](../../../Engine/Log)
- [PonyEngine.Application.Ext](../Application.Ext)

## CMake variables

These variables are used to configure the build of the module:

| Variable name            | Default value | Description                                       |
|:-------------------------|:-------------:|:--------------------------------------------------|
| `PONY_ENGINE_FILE_ORDER` | p             | PonyEngine.File.Impl module initialization order. |

## For Pony Engine developers

Main sub-modules:

### [File](Source/Main-File.cppm)

File wrapper.

### [FileService](Source/Main-FileService.cppm)

File service implementation.

### [FileServiceModule](Source/Main-FileServiceModule.cppm)

File service module.

### [Worker](Source/Main-Worker.cppm)

Worker that manages IO thread.
