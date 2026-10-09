# PonyEngine.Resource.World.Impl feature module

World resource module implementation.

## Dependencies

- [PonyEngine.Core](../Core)
- [PonyEngine.Job](../Job)
- [PonyEngine.Log](../Log)
- [PonyEngine.Resource](../Resource)
- [PonyEngine.Resource.Ext](../Resource.Ext)
- [PonyEngine.Resource.World](../Resource.World)
- [PonyEngine.World](../World)

## CMake variables

These variables are used to configure the build of the module:

| Variable name                            | Default value | Description                                                 |
|:-----------------------------------------|:-------------:|:------------------------------------------------------------|
| `PONY_ENGINE_RESOURCE_WORLD_ORDER`       | p             | PonyEngine.Resource.World.Impl module initialization order. |

## For Pony Engine developers

Main sub-modules:

- [WorldDefinitionLoader](Source/World-WorldDefinitionLoader.cppm) - world definition resource loader;
- [WorldDefinitionLoaderModule](Source/World-WorldDefinitionLoaderModule.cppm) - world definition resource loader module.
