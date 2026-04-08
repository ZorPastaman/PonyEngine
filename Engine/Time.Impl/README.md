# PonyEngine.Time.Impl module

Time implementation module.

## Dependencies

- [PonyEngine.Core](../Core)
- [PonyEngine.Log](../Log)
- [PonyEngine.Application.Ext](../Application.Ext)
- [PonyEngine.Time](../Time)

## CMake variables

These variables are used to configure the build of the module:

| Variable name                 | Default value | Description                                       |
|:------------------------------|:-------------:|:--------------------------------------------------|
| `PONY_ENGINE_TIME_ORDER`      | p             | PonyEngine.Time.Impl module initialization order. |
| `PONY_ENGINE_TIME_TICK_ORDER` | 0             | Time service tick order.                          |

## For Pony Engine developers

Main sub-modules:

- [TimeService](Source/Private/Main-TimeService.cppm) - time service;
- [TimeServiceModule](Source/Private/Main-TimeServiceModule.cppm) - time service module.

In its tick the time service waits for a target frame time first of all. It's done in busy waiting style.
Then it calculates all its properties based on time differences and current parameters.
