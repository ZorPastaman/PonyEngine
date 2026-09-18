# PonyEngine.Time.Impl feature module

Time service implementation module.

Adds `PonyEngine.Time.Impl` target as a static library.

## Dependencies

- [PonyEngine.Application](../Application)
- [PonyEngine.Core](../Core)
- [PonyEngine.Log](../Log)
- [PonyEngine.Time](../Time)

## CMake variables

These variables are used to configure the build of the module:

| Variable name                        | Default value | Description                                        |
|:-------------------------------------|:-------------:|:---------------------------------------------------|
| `PONY_ENGINE_TIME_ORDER`             | p             | PonyEngine.Time.Impl module initialization order.  |
| `PONY_ENGINE_TIME_TICK_ORDER`        | 0             | Time service tick order.                           |
| `PONY_ENGINE_TIME_DELTA_TIME_CAP`    | 1.0           | Time service initial delta time cap in seconds.    |
| `PONY_ENGINE_TIME_SCALE`             | 1.0           | Time service initial scale.                        |
| `PONY_ENGINE_TIME_FIXED_STEP_PERIOD` | 1.0 / 60.0    | Time service initial fixed step period in seconds. |

## For Pony Engine developers

Main sub-modules:

- [TimeService](Source/Time-TimeService.cppm) - time service;
- [TimeServiceModule](Source/Time-TimeServiceModule.cppm) - time service module.
