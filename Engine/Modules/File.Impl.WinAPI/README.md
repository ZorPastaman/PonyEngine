# PonyEngine.File.Impl.WinAPI modification module

Adds WinAPI implementation to [PonyEngine.File.Impl](../File.Impl).

Modifies `PonyEngine.File.Impl` target.

## Dependencies

- [PonyEngine.Application](../Application)
- [PonyEngine.File.Impl](../File.Impl)
- [PonyEngine.Log](../Log)
- Windows SDK 10.0.26100.0

## CMake variables

These variables are used to configure the build of the module:

| Variable name                  | Default value | Description                                       |
|:-------------------------------|:-------------:|:--------------------------------------------------|
| `PONY_ENGINE_FILE_ORDER`       | p             | PonyEngine.File.Impl module initialization order. |
| `PONY_ENGINE_FILE_THREAD_ROLE` | IO            | PonyEngine.File.Impl io thread role.              |

## For Pony Engine developers

### [File](Source/File-File.cppm)

File wrapper.

### [FileService](Source/File-FileService.cppm)

File service implementation.

### [FileServiceModule](Source/File-FileServiceModule.cppm)

File service module.

### [Worker](Source/File-Worker.cppm)

Worker that manages IO thread.
