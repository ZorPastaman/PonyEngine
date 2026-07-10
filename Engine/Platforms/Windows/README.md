# Windows platform support

## Prerequisites

- Windows SDK 10.0.26100.0 or higher

## Modules

The Windows support mutates engine modules, adding code and defines to them.

| Engine module                                                                         | Windows platform module                                                         |
|:--------------------------------------------------------------------------------------|:--------------------------------------------------------------------------------|
| [PonyEngine.Core](../../Modules/Core)                                                 | [PonyEngine.Core.Windows](Core)                                                 |
| [PonyEngine.Application.Ext](../../Modules/Application.Ext)                           | [PonyEngine.Application.Ext.Windows](Application.Ext)                           |
| [PonyEngine.Application.Impl](../../Modules/Application.Impl)                         | [PonyEngine.Application.Impl.Windows](Application.Impl)                         |
| [PonyEngine.File.Impl](../../Modules/File.Impl)                                       | [PonyEngine.File.Impl.Windows](File.Impl)                                       |
| [PonyEngine.MessagePump.Impl](../../Modules/MessagePump.Impl)                         | [PonyEngine.MessagePump.Impl.Windows](MessagePump.Impl)                         |
| [PonyEngine.RawInput.Keyboard.Impl](../../Modules/RawInput.Keyboard.Impl)             | [PonyEngine.RawInput.Keyboard.Impl.Windows](RawInput.Keyboard.Impl)             |
| [PonyEngine.RawInput.Mouse.Impl](../../Modules/RawInput.Mouse.Impl)                   | [PonyEngine.RawInput.Mouse.Impl.Windows](RawInput.Keyboard.Impl)                |
| [PonyEngine.RawInput.XInput.Impl](../../Modules/RawInput.XInput.Impl)                 | [PonyEngine.RawInput.XInput.Impl.Windows](RawInput.XInput.Impl)                 |
| [PonyEngine.RenderDevice.D3D12.Impl](../../Modules/RenderDevice.D3D12.Impl)           | [PonyEngine.RenderDevice.D3D12.Impl.Windows](RenderDevice.D3D12.Impl) |
| [PonyEngine.Surface](../../Modules/Surface)                                           | [PonyEngine.Surface.Windows](Surface)                                           |
| [PonyEngine.Surface.Impl](../../Modules/Surface.Impl)                                 | [PonyEngine.Surface.Impl.Windows](Surface.Impl)                                 |

## Long paths

Long paths support is not implemented.

## For Pony Engine developers

Windows SDK version 10.0.26100.0 is required to ensure compatibility. Other versions will fail the build.
