# PonyEngine.World.Impl feature module

World service implementation module.

## Dependencies

- [PonyEngine.Application](../Application)
- [PonyEngine.Core](../Core)
- [PonyEngine.Log](../Log)
- [PonyEngine.World](../World)

## CMake variables

These variables are used to configure the build of the module:

| Variable name             | Default value | Description                                        |
|:--------------------------|:-------------:|:---------------------------------------------------|
| `PONY_ENGINE_WORLD_ORDER` | p             | PonyEngine.World.Impl module initialization order. |

## For Pony Engine developers

Main sub-modules:

- [ComponentTable](Source/World-ComponentTable.cppm) - typeless component table, it manages them using component size and alignment;
- [ObjectTable](Source/World-ObjectTable.cppm) - typeless object table;
- [TypeRegistry](Source/World-TypeRegistry.cppm) - registry that holds info about component and object types;
- [World](Source/World-World.cppm) - world container;
- [WorldService](Source/World-WorldService.cppm) - world service;
- [WorldServiceModule](Source/World-WorldServiceModule.cppm) - world service module.
