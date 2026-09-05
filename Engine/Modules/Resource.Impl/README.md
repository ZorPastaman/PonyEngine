# PonyEngine.Resource.Impl feature module

Resource implementation module.

Adds `PonyEngine.Resource.Impl` target as a static library.

## Dependencies

- [PonyEngine.Application](../Application)
- [PonyEngine.Core](../Core)
- [PonyEngine.Log](../Log)
- [PonyEngine.Resource](../Resource)
- [PonyEngine.Resource.Ext](../Resource.Ext)

## CMake variables

These variables are used to configure the build of the module:

| Variable name                     | Default value | Description                                           |
|:----------------------------------|:-------------:|:------------------------------------------------------|
| `PONY_ENGINE_RESOURCE_ORDER`      | p             | PonyEngine.Resource.Impl module initialization order. |
| `PONY_ENGINE_RESOURCE_TICK_ORDER` | 0             | Resource service tick order.                          |

## For Pony Engine developers

Main sub-modules:

- [ResourceService](Source/Resource-ResourceService.cppm) - resource service;
- [ResourceServiceModule](Source/Resource-ResourceServiceModule.cppm) - resource service module.
