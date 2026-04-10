# PonyEngine.MessagePump.Impl module for Windows

Platform independent module: [PonyEngine.MessagePump.Impl](../../../Engine/MessagePump.Impl).

## Dependencies

- [PonyEngine.Core](../Core)
- [PonyEngine.Log](../../../Engine/Log)
- [PonyEngine.Application.Ext](../Application.Ext)

## CMake variables

These variables are used to configure the build of the module:

| Variable name                         | Default value | Description                                              |
|:--------------------------------------|:-------------:|:---------------------------------------------------------|
| `PONY_ENGINE_MESSAGE_PUMP_ORDER`      | p             | PonyEngine.MessagePump.Impl module initialization order. |
| `PONY_ENGINE_MESSAGE_PUMP_TICK_ORDER` | 0             | PonyEngine.MessagePump.Impl service tick order.          |

## For Pony Engine developers

Main submodules:

- [MessagePumpService](Source/Main-MessagePumpService.cppm) - message pump service;
- [MessagePumpServiceModule](Source/Main-MessagePumpServiceModule.cppm) - message pump service module.
