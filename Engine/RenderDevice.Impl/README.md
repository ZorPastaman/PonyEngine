# PonyEngine.RenderDevice.Impl module

Render device implementation module.

## Dependencies

- [PonyEngine.Core](../Core)
- [PonyEngine.Log](../Log)
- [PonyEngine.Application.Ext](../Application.Ext)
- [PonyEngine.RenderDevice](../RenderDevice)
- [PonyEngine.RenderDevice.Ext](../RenderDevice.Ext)

## CMake variables

These variables are used to configure the build of the module:

| Variable name                     | Default value | Description                                               |
|:----------------------------------|:-------------:|:----------------------------------------------------------|
| `PONY_ENGINE_RENDER_DEVICE_ORDER` | p             | PonyEngine.RenderDevice.Impl module initialization order. |

## For Pony Engine developers

Main sub-modules:

- [RenderDeviceService](Source/Main-RenderDeviceService.cppm) - raw input service;
- [RenderDeviceServiceModule](Source/Main-RenderDeviceServiceModule.cppm) - raw input service module.
