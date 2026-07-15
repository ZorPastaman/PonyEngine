# PonyEngine.Resource.Pack.Impl module

Pack resource provider implementation module. 
It's a provider that manages resource packs - files that contain many resources.

## Dependencies

- [PonyEngine.Core](../Core)
- [PonyEngine.Log](../Log)
- [PonyEngine.Application](../Application)
- [PonyEngine.File](../File)
- [PonyEngine.Resource](../Resource)
- [PonyEngine.Resource.Ext](../Resource.Ext)

## CMake variables

These variables are used to configure the build of the module:

| Variable name                            | Default value             | Description                                                |
|:-----------------------------------------|:-------------------------:|:-----------------------------------------------------------|
| `PONY_ENGINE_RESOURCE_PACK_ORDER`        | p                         | PonyEngine.Resource.Pack.Impl module initialization order. |
| `PONY_ENGINE_RESOURCE_PACK_MANIFEST_DIR` | "Manifests/Resource/Pack" | Pack resource manifest directory.                          |

## For Pony Engine developers

Main sub-modules:

- [PackResourceProvider](Source/Main-PackResourceProvider.cppm) - pack resource provider;
- [PackResourceProviderModule](Source/Main-PackResourceProviderModule.cppm) - pack resource provider module.
