# PonyEngine.Resource.World.Hierarchy.Impl feature module

Adds hierarchy component deserializers to the world definition loader.

Adds `PonyEngine.Resource.World.Hierarchy.Impl` target.

## Dependencies

- [PonyEngine.Core](../Core)
- [PonyEngine.Resource.World](../Resource.World)
- [PonyEngine.World.Hierarchy](../World.Hierarchy)

## CMake variables

These variables are used to configure the build of the module:

| Variable name                                | Default value | Description                                                           |
|:---------------------------------------------|:-------------:|:----------------------------------------------------------------------|
| `PONY_ENGINE_RESOURCE_WORLD_HIERARCHY_ORDER` | p             | PonyEngine.Resource.World.Hierarchy.Impl module initialization order. |

## For Pony Engine developers

Main sub-modules:

- [Transform2DDeserializer](Source/Hierarchy-Transform2DDeserializer.cppm) - transform 2D deserializer.
- [Transform3DDeserializer](Source/Hierarchy-Transform2DDeserializer.cppm) - transform 3D deserializer.
- [HierarchyDesrializerModule](Source/Hierarchy-HierarchyDeserializerModule.cppm) - hierarchy deserializer module.
