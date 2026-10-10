# PonyEngine.Resource.World.Hierarchy.Impl feature module

Adds hierarchy component deserializers to the world definition loader.

It deserializes Parent and LocalTransform2D(3D) components only. All other hierarchy components are runtime only.
The deserialized components are pure data and their serialized versions are simply copied to a world definition.
The Parent component should have an index reference to its parent.

Component types:

| Type                                             | Serialized type    |
|:-------------------------------------------------|:-------------------|
| `PonyEngine::World::Hierarchy::Parent`           | `Pony.Parent`      |
| `PonyEngine::World::Hierarchy::LocalTransform2D` | `Pony.Transform2D` |
| `PonyEngine::World::Hierarchy::LocalTransform3D` | `Pony.Transform3D` |

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

- [HierarchyDesrializerModule](Source/Hierarchy-HierarchyDeserializerModule.cppm) - hierarchy deserializer module.
