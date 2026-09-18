# PonyEngine.RawInput.XInput.Impl feature module

Raw input XInput provider module. It reads XInput input and pushes it into a raw input device hub.

The module requires WinAPI support.

Adds `PonyEngine.RawInput.XInput.Impl` target as a static library.

## Dependencies

- [PonyEngine.Application](../Application)
- [PonyEngine.Core](../Core)
- [PonyEngine.Log](../Log)
- [PonyEngine.RawInput](../RawInput)
- [PonyEngine.RawInput.Ext](../RawInput.Ext)
- Windows SDK 10.0.26100.0

## For Pony Engine developers

Main submodules:

- [XInputProvider](Source/XInput-XInputProvider.cppm) - XInput provider;
- [XInputProviderModule](Source/XInput-XInputProviderModule.cppm) - XInput provider module.

