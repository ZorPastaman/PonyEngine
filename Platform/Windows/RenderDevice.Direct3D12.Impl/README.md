# PonyEngine.RenderDevice.Direct3D12.Impl module for Windows

Platform independent module: [PonyEngine.RenderDevice.Direct3D12.Impl](../../../Engine/RenderDevice.Direct3D12.Impl).

## Dependencies

- [PonyEngine.Core](../Core)
- [PonyEngine.Log](../../../Engine/Log)
- [PonyEngine.Application.Ext](../Application.Ext)
- [PonyEngine.Surface](../Surface)
- d3d12.lib (Windows SDK)
- dxgi.lib (Windows SDK)
- dxguid.lib (Windows SDK)

## GPU requirements

- Feature level 12.2
- Enhanced barriers support
- Relaxed format casting support
- Alpha blend factor support
- Independent front and back stencil reference mask support
- Dynamic depth bias support
- Rasterizer description 2 support

## CMake variables

These variables are used to configure the build of the module:

| Variable name                                | Default value | Description                                                          |
|:---------------------------------------------|:-------------:|:---------------------------------------------------------------------|
| `PONY_ENGINE_RENDER_DEVICE_DIRECT3D12_ORDER` | p             | PonyEngine.RenderDevice.Direct3D12.Impl module initialization order. |

## For Pony Engine developers

Main sub-modules:

### [Factory](Source/Private/Main-Factory.cppm)

DXGI factory wrapper.

### [Device](Source/Private/Main-Device.cppm)

D3D12 device wrapper.

### [Engine](Source/Private/Main-Engine.cppm)

Main class of the Direct3D 12 implementation. It's the actual class that is accessed by the render device service.

### [Backend](Source/Private/Main-Backend.cppm)

Facade class that is accessed by the render device service directly. It just has a `std::unique_ptr<Engine>` and translates all the calls to it.
This way, the backend footprint is kept as minimal as possible when it's not active.

### [BackendModule](Source/Private/Main-BackendModule.cppm)

Direct3D12 backend module.
