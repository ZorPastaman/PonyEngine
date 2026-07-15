# PonyEngine.World.Impl module

World service implementation module.

## Dependencies

- [PonyEngine.Core](../Core)
- [PonyEngine.Log](../Log)
- [PonyEngine.Application](../Application)
- [PonyEngine.World](../World)

## CMake variables

These variables are used to configure the build of the module:

| Variable name             | Default value | Description                                        |
|:--------------------------|:-------------:|:---------------------------------------------------|
| `PONY_ENGINE_WORLD_ORDER` | p             | PonyEngine.World.Impl module initialization order. |

## For Pony Engine developers

Main sub-modules:

- [ComponentTable](Source/Main-ComponentTable.cppm) - typeless component table, it manages them using component size and alignment;
- [ObjectTable](Source/Main-ObjectTable.cppm) - typeless object table;
- [TypeRegistry](Source/Main-TypeRegistry.cppm) - registry that holds info about component and object types;
- [World](Source/Main-World.cppm) - world container;
- [WorldService](Source/Main-WorldService.cppm) - world service;
- [WorldServiceModule](Source/Main-WorldServiceModule.cppm) - world service module.
