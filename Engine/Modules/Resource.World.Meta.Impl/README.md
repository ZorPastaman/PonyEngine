# PonyEngine.Resource.World.Meta.Impl feature module

Adds meta component deserializers to the world definition loader.

## Dependencies

- [PonyEngine.Core](../Core)
- [PonyEngine.Resource.World](../Resource.World)
- [PonyEngine.World.Meta](../World.Meta)

## CMake variables

These variables are used to configure the build of the module:

| Variable name                           | Default value | Description                                                      |
|:----------------------------------------|:-------------:|:-----------------------------------------------------------------|
| `PONY_ENGINE_RESOURCE_WORLD_META_ORDER` | p             | PonyEngine.Resource.World.Meta.Impl module initialization order. |

## For Pony Engine developers

Main sub-modules:

- [NameDeserializer](Source/Meta-NameDeserializer.cppm) - name deserializer.
- [MetaDesrializerModule](Source/Meta-MetaDeserializerModule.cppm) - meta deserializer module.
