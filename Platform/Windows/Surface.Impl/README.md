# PonyEngine.Surface.Impl module for Windows

Platform independent module: [PonyEngine.Surface.Impl](../../../Engine/Surface.Impl).

## Dependencies

- [PonyEngine.Core](../Core)
- [PonyEngine.Log](../../../Engine/Log)
- [PonyEngine.Application.Ext](../Application.Ext)
- [PonyEngine.MessagePump](../../../Engine/MessagePump)

## CMake variables

These variables are used to configure the build of the module:

| Variable name               | Default value | Description                                          |
|:----------------------------|:-------------:|:-----------------------------------------------------|
| `PONY_ENGINE_SURFACE_ORDER` | p             | PonyEngine.Surface.Impl module initialization order. |

## For Pony Engine developers

Main sub-modules:

### [MessageHandler](Source/Main-MessageHandler.cppm)

Utilities to make Windows message handling object oriented.

A window class must use `WindowProc()` as a window proc function.
A surface service must inherit `IMessageHandler` and put a pointer to its implementation in `CreateWindowExA()` lpParam.

### [WindowClass](Source/Main-WindowClass.cppm)

Window class holder.

### [SurfaceService](Source/Main-SurfaceService.cppm)

Surface service implementation.

The service creates a window on its constructor but shows it only on `Begin()`.

### [SurfaceServiceModule](Source/Main-SurfaceServiceModule.cppm)

Surface service module.
