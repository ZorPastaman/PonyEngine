# Windows platform support

## Prerequisites

- Windows SDK 10.0.26100.0 or higher

## Modules

The Windows support mutates engine modules, adding code and defines to them.

| Engine module                                                                        | Windows platform module                                                         |
|:-------------------------------------------------------------------------------------|:--------------------------------------------------------------------------------|
| [PonyEngine.Core](../../Engine/Core)                                                 | [PonyEngine.Core.Windows](Core)                                                 |
| [PonyEngine.Application.Ext](../../Engine/Application.Ext)                           | [PonyEngine.Application.Ext.Windows](Application.Ext)                           |
| [PonyEngine.Application.Impl](../../Engine/Application.Impl)                         | [PonyEngine.Application.Impl.Windows](Application.Impl)                         |
| [PonyEngine.MessagePump.Impl](../../Engine/MessagePump.Impl)                         | [PonyEngine.MessagePump.Impl.Windows](MessagePump.Impl)                         |
| [PonyEngine.RawInput.Keyboard.Impl](../../Engine/RawInput.Keyboard.Impl)             | [PonyEngine.RawInput.Keyboard.Impl.Windows](RawInput.Keyboard.Impl)             |
| [PonyEngine.RawInput.Mouse.Impl](../../Engine/RawInput.Mouse.Impl)                   | [PonyEngine.RawInput.Mouse.Impl.Windows](RawInput.Keyboard.Impl)                |
| [PonyEngine.RawInput.XInput.Impl](../../Engine/RawInput.XInput.Impl)                 | [PonyEngine.RawInput.XInput.Impl.Windows](RawInput.XInput.Impl)                 |
| [PonyEngine.RenderDevice.Direct3D12.Impl](../../Engine/RenderDevice.Direct3D12.Impl) | [PonyEngine.RenderDevice.Direct3D12.Impl.Windows](RenderDevice.Direct3D12.Impl) |
| [PonyEngine.Surface](../../Engine/Surface)                                           | [PonyEngine.Surface.Windows](Surface)                                           |
| [PonyEngine.Surface.Impl](../../Engine/Surface.Impl)                                 | [PonyEngine.Surface.Impl.Windows](Surface.Impl)                                 |

## For Pony Engine developers

Windows SDK version 10.0.26100.0 is required to ensure compatibility. Other versions will fail the build.
