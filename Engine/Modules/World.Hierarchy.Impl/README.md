# PonyEngine.World.Hierarchy.Impl feature module

World hierarchy implementation module.

On its initialization it registers all the hierarchy components. No need for that from a project code.

## Dependencies

- [PonyEngine.Core](../Core)
- [PonyEngine.World](../World)
- [PonyEngine.World.Hierarchy](../World.Hierarchy)

## CMake variables

These variables are used to configure the build of the module:

| Variable name                       | Default value | Description                                                  |
|:------------------------------------|:-------------:|:-------------------------------------------------------------|
| `PONY_ENGINE_WORLD_HIERARCHY_ORDER` | p             | PonyEngine.World.Hierarchy.Impl module initialization order. |

## For Pony Engine developers

Main submodules:

- [HierarchyService](Source/Hierarchy-HierarchyService.cppm) - hierarchy service;
- [HierarchyServiceModule](Source/Hierarchy-HierarchyServiceModule.cppm) - hierarchy service module.
