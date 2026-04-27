# PonyEngine.Time.Impl module

Time implementation module.

## Dependencies

- [PonyEngine.Log](../Log)
- [PonyEngine.Application.Ext](../Application.Ext)
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
| `PONY_ENGINE_TIME_TARGET_FRAME_TIME` | 0.0           | Time service initial target frame time in seconds. |

## For Pony Engine developers

Main sub-modules:

- [TimeService](Source/Main-TimeService.cppm) - time service;
- [TimeServiceModule](Source/Main-TimeServiceModule.cppm) - time service module.

In its tick the time service waits for a target frame time first of all. It's done in busy waiting style.
Then it calculates all its properties based on time differences and current parameters.
