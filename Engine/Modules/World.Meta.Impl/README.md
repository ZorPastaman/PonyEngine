# PonyEngine.World.Meta.Impl feature module

World meta implementation module.

On its initialization it registers all the meta components. No need for that from a project code.

Adds `PonyEngine.World.Meta.Impl` target.

## Dependencies

- [PonyEngine.Application](../Application)
- [PonyEngine.Core](../Core)
- [PonyEngine.World](../World)
- [PonyEngine.World.Meta](../World.Meta)

## CMake variables

These variables are used to configure the build of the module:

| Variable name                  | Default value | Description                                             |
|:-------------------------------|:-------------:|:--------------------------------------------------------|
| `PONY_ENGINE_WORLD_META_ORDER` | p             | PonyEngine.World.Meta.Impl module initialization order. |

## For Pony Engine developers

Main submodules:

- [MetaModule](Source/Meta-MetaModule.cppm) - meta module.
