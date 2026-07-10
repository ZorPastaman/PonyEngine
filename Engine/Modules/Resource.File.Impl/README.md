# PonyEngine.Resource.File.Impl module

File resource provider implementation module. 
It's a provider where every resource corresponds to an individual file in a game directory.

## Dependencies

- [PonyEngine.Core](../Core)
- [PonyEngine.Log](../Log)
- [PonyEngine.Application.Ext](../Application.Ext)
- [PonyEngine.File](../File)
- [PonyEngine.Resource](../Resource)
- [PonyEngine.Resource.Ext](../Resource.Ext)

## CMake variables

These variables are used to configure the build of the module:

| Variable name                            | Default value             | Description                                                |
|:-----------------------------------------|:-------------------------:|:-----------------------------------------------------------|
| `PONY_ENGINE_RESOURCE_FILE_ORDER`        | p                         | PonyEngine.Resource.File.Impl module initialization order. |
| `PONY_ENGINE_RESOURCE_FILE_MANIFEST_DIR` | "Manifests/Resource/File" | File resource manifest directory.                          |

## For Pony Engine developers

Main sub-modules:

- [FileResourceProvider](Source/Main-FileResourceProvider.cppm) - file resource provider;
- [FileResourceProviderModule](Source/Main-FileResourceProviderModule.cppm) - file resource provider module.
