# PonyEngine.Resource.Pack.Impl module

Pack resource provider module.

## Dependencies

- [PonyEngine.Application](../Application)
- [PonyEngine.Core](../Core)
- [PonyEngine.File](../File)
- [PonyEngine.Job](../Job)
- [PonyEngine.Log](../Log)
- [PonyEngine.Resource](../Resource)
- [PonyEngine.Resource.Ext](../Resource.Ext)
- [PonyEngine.Resource.Pack](../Resource.Pack)

## CMake variables

These variables are used to configure the build of the module:

| Variable name                            | Default value             | Description                                                |
|:-----------------------------------------|:-------------------------:|:-----------------------------------------------------------|
| `PONY_ENGINE_RESOURCE_PACK_ORDER`        | p                         | PonyEngine.Resource.Pack.Impl module initialization order. |

## For Pony Engine developers

Main sub-modules:

- [PackService](Source/Main-PackService.cppm) - pack resource service;
- [PackServiceModule](Source/Main-PackServiceModule.cppm) - pack resource service module.
